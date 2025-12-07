#!/usr/bin/env bash
# ═══════════════════════════════════════════════════════════════════════════════
# Bongo Cat - Input Device Discovery Tool v4.0.0
# Interactive keyboard detection by listening for actual key events
# ═══════════════════════════════════════════════════════════════════════════════

set -euo pipefail

VERSION="4.0.0"
SCRIPT_NAME="wpets-find-devices"

# Colors
if [[ -t 1 ]] && [[ "${NO_COLOR:-}" != "1" ]]; then
  RED='\033[0;31m' GREEN='\033[0;32m' YELLOW='\033[1;33m'
  BLUE='\033[0;34m' CYAN='\033[0;36m' BOLD='\033[1m' DIM='\033[2m' NC='\033[0m'
else
  RED='' GREEN='' YELLOW='' BLUE='' CYAN='' BOLD='' DIM='' NC=''
fi

# ─────────────────────────────────────────────────────────────────────────────
# Helper Functions
# ─────────────────────────────────────────────────────────────────────────────

info()    { echo -e "${BLUE}→${NC} $*"; }
success() { echo -e "${GREEN}✓${NC} $*"; }
warn()    { echo -e "${YELLOW}!${NC} $*"; }
error()   { echo -e "${RED}✗${NC} $*" >&2; }

header() {
  echo
  echo -e "${BOLD}$*${NC}"
  echo -e "${BLUE}$(printf '─%.0s' {1..60})${NC}"
}

# ─────────────────────────────────────────────────────────────────────────────
# Device Discovery
# ─────────────────────────────────────────────────────────────────────────────

device_is_ignored() {
    local name="$1"
    shift
    local ignore_devices=("$@")
    for pattern in "${ignore_devices[@]}"; do
        if [[ "$name" =~ $pattern ]]; then
            return 0  # ignored
        fi
    done
    return 1  # not ignored
}

# Get all event devices with kbd handler (potential keyboards)
get_kbd_devices() {
  local prefer_byid="$1"   # "true" = prefer /dev/input/by-id symlinks
  shift 1
  local ignore_devices=("$@")   # now receives array properly

  local devices=()

  if [[ ! -r /proc/bus/input/devices ]]; then
    return 1
  fi

  local name="" handlers="" capabilities=""

  while IFS= read -r line; do
    case "$line" in
      N:\ Name=\"*\")
        name="${line#N: Name=\"}"
        name="${name%\"}"
        ;;
      H:\ Handlers=*)
        handlers="${line#H: Handlers=}"
        ;;
      B:\ EV=*)
        capabilities="${line#B: EV=}"
        ;;
      "")
        if [ ${#ignore_devices[@]} -gt 0 ]; then
          # Skip ignored devices
          if device_is_ignored "$name" "${ignore_devices[@]}"; then
              name="" handlers="" capabilities=""
              continue
          fi
        fi
        if [[ "$handlers" =~ kbd ]] && [[ "$handlers" =~ event ]]; then
          local event
          event=$(echo "$handlers" | grep -o 'event[0-9]*' | head -1)
          local real_path="/dev/input/$event"
          if [[ -n "$event" ]] && [[ -e "$real_path" ]]; then
            local device_path="$real_path"
            if [[ "$prefer_byid" == "true" ]]; then
                local symlink
                symlink=$(find -L /dev/input/by-id/ -samefile "$real_path" -print -quit 2>/dev/null)
                [[ -n "$symlink" ]] && device_path="$symlink"
            fi
            devices+=("$event|$name|$handlers|$capabilities|$device_path")
          fi
        fi
        name="" handlers="" capabilities=""
        ;;
    esac
  done < /proc/bus/input/devices

  printf '%s\n' "${devices[@]}"
}

# Check if device is readable
check_device() {
  local path="$1"
  [[ -r "$path" ]]
}

# ─────────────────────────────────────────────────────────────────────────────
# Interactive Detection
# ─────────────────────────────────────────────────────────────────────────────

# Listen for key events on a device (runs in background)
listen_device() {
  local device="$1"
  local output_file="$2"
  local timeout="$3"

  # Use timeout + cat to read raw events
  # Key events are detected by the presence of specific byte patterns
  # Type 1 (EV_KEY) events indicate keyboard activity
  timeout "$timeout" cat "/dev/input/$device" 2>/dev/null | head -c 1000 > "$output_file" &
  echo $!
}

# Detect keyboards interactively
interactive_detect() {
  local timeout="${1:-5}"
  local prefer_byid="$2"   # "true" = prefer /dev/input/by-id symlinks
  local devices
  devices=$(get_kbd_devices "${prefer_byid}") || { error "Cannot read device list"; return 1; }

  if [[ -z "$devices" ]]; then
    error "No input devices with kbd handler found"
    info "Try: sudo $SCRIPT_NAME --interactive"
    return 1
  fi

  # Check permissions
  local has_permission=false
  while IFS='|' read -r event name handlers device_path; do
    if check_device "/dev/input/$event"; then
      has_permission=true
      break
    fi
  done <<< "$devices"

  if [[ "$has_permission" == "false" ]]; then
    error "Cannot read input devices (permission denied)"
    echo
    info "Fix with: ${CYAN}sudo usermod -a -G input \$USER${NC}"
    info "Then log out and back in"
    echo
    info "Or run: ${CYAN}sudo $SCRIPT_NAME --interactive${NC}"
    return 1
  fi

  # Create temp directory for output files
  local tmpdir
  tmpdir=$(mktemp -d)
  trap "rm -rf '$tmpdir'" EXIT

  header "Interactive Keyboard Detection"
  echo
  echo -e "  ${BOLD}Press keys on ALL your keyboards for ${timeout} seconds...${NC}"
  echo -e "  ${DIM}(Internal laptop keyboard, external keyboards, etc.)${NC}"
  echo

  # Start listening on all accessible devices
  local pids=()
  local device_list=()

  while IFS='|' read -r event name handlers device_path; do
    if check_device "/dev/input/$event"; then
      local outfile="$tmpdir/$event"
      local pid
      pid=$(listen_device "$event" "$outfile" "$timeout")
      pids+=("$pid")
      device_list+=("$event|$name|$outfile|$device_path")
    fi
  done <<< "$devices"

  # Show countdown
  for ((i=timeout; i>0; i--)); do
    echo -ne "\r  ${CYAN}Listening... ${i}s remaining ${NC}  "
    sleep 1
  done
  echo -e "\r  ${GREEN}✓ Detection complete!${NC}              "

  # Wait for all listeners to finish
  for pid in "${pids[@]}"; do
    wait "$pid" 2>/dev/null || true
  done

  echo

  # Check which devices received input
  local detected_keyboards=()
  local other_devices=()

  for entry in "${device_list[@]}"; do
    IFS='|' read -r event name outfile device_path <<< "$entry"

    if [[ -s "$outfile" ]]; then
      # Device received input - it's a keyboard!
      detected_keyboards+=("$event|$name|$device_path")
    else
      other_devices+=("$event|$name|$device_path")
    fi
  done

  # Show results
  header "Detection Results"

  if [[ ${#detected_keyboards[@]} -eq 0 ]]; then
    warn "No keyboards detected"
    echo
    info "Make sure you pressed keys during the detection window"
    info "Try again with: $SCRIPT_NAME --interactive"
    return 1
  fi

  echo -e "  ${GREEN}Detected keyboards:${NC}"
  for entry in "${detected_keyboards[@]}"; do
    IFS='|' read -r event name device_path <<< "$entry"
    echo -e "    ${GREEN}✓${NC} ${BOLD}$name${NC}"
    echo -e "      ${CYAN}$device_path${NC}"
  done

  if [[ ${#other_devices[@]} -gt 0 ]]; then
    echo
    echo -e "  ${DIM}Other devices (no input detected):${NC}"
    for entry in "${other_devices[@]}"; do
      IFS='|' read -r event name device_path <<< "$entry"
      echo -e "    ${DIM}○ $name (/dev/input/$event)${NC}"
    done
  fi

  # Config suggestion
  header "Add to Config"
  echo -e "  ${BOLD}~/.config/bongocat/bongocat.conf:${NC}"
  echo
  for entry in "${detected_keyboards[@]}"; do
    IFS='|' read -r event name device_path <<< "$entry"
    echo -e "  ${CYAN}keyboard_device=$device_path${NC}  ${BOLD}# $name${NC}"
  done

  echo
}

# ─────────────────────────────────────────────────────────────────────────────
# Quick Mode (non-interactive, name-based)
# ─────────────────────────────────────────────────────────────────────────────

# Guess if device is keyboard by name
is_likely_keyboard() {
  local name="$1"
  local name_lower
  name_lower=$(echo "$name" | tr '[:upper:]' '[:lower:]')

  # Exclude obvious non-keyboards
  [[ "$name_lower" =~ (button|hotkey|speaker|video|consumer|system|avrcp|mouse|touchpad|trackpad) ]] && return 1

  # Include devices with "keyboard" in name
  [[ "$name_lower" =~ keyboard ]] && return 0

  # Include standard laptop keyboard
  [[ "$name_lower" =~ "at translated set 2" ]] && return 0

  return 1
}
is_likely_mouse() {
  local name="$1"
  local name_lower
  name_lower=$(echo "$name" | tr '[:upper:]' '[:lower:]')

  # obvious non-keyboards
  [[ "$name_lower" =~ (mouse|touchpad|trackpad) ]] && return 0

  # Include devices with "mouse" in name
  [[ "$name_lower" =~ mouse ]] && return 0

  return 1
}

generate_config() {
  local devices=("$@")

  if [[ -z "$devices" ]]; then
    return 1
  fi

  # Calculate max path length for alignment
  local maxlen=0
  for entry in "${devices[@]}"; do
      IFS='|' read -r event name device_path <<< "$entry"
      [[ ${#device_path} -gt $maxlen ]] && maxlen=${#device_path}
  done

  # Config suggestion
  for entry in "${devices[@]}"; do
    IFS='|' read -r event name device_path <<< "$entry"
    #echo -e "  ${CYAN}keyboard_device=$device_path${NC}  ${BOLD}# $name${NC}"
    printf "${CYAN}keyboard_device=%-${maxlen}s${NC}   ${BOLD}# %s ${NC}\n" "$device_path" "$name"
  done
}

get_device_type() {
    local device_name="$1"
    local handlers="$2"
    local capabilities="$3"

    # Convert to lowercase for matching
    local name_lower=$(echo "$device_name" | tr '[:upper:]' '[:lower:]')
    local handlers_lower=$(echo "$handlers" | tr '[:upper:]' '[:lower:]')

    # Check for keyboard indicators
    # Look for "kbd" handler (most reliable), keyboard in name, or keyboard-like capabilities
    if [[ "$name_lower" =~ mouse ]] || [[ "$handlers_lower" =~ mouse ]]; then
        echo "MOUSE"
    elif [[ "$name_lower" =~ keyboard ]] || [[ "$capabilities" =~ "120013" ]] || [[ "$capabilities" =~ "12001f" ]]; then
        # Determine keyboard type
        if [[ "$name_lower" =~ (bluetooth|wireless|bt) ]] || [[ "$handlers_lower" =~ bluetooth ]]; then
            echo "KEYBOARD"
        elif [[ "$name_lower" =~ (usb|external) ]]; then
            echo "KEYBOARD"
        else
            # Check if it's likely a Bluetooth keyboard based on common brands
            if [[ "$name_lower" =~ (keychron|logitech|corsair|razer|steelseries|apple|microsoft) ]] && [[ ! "$name_lower" =~ (mouse|trackpad|touchpad) ]]; then
                echo "KEYBOARD"
            else
                echo "KEYBOARD"
            fi
        fi
    elif [[ "$capabilities" =~ (110000|17|7) ]]; then
        echo "MOUSE"
    elif [[ "$name_lower" =~ (touchpad|trackpad|synaptics) ]]; then
        echo "Touchpad"
    elif [[ "$name_lower" =~ (touchscreen|touch) ]]; then
        echo "Touchscreen"
    elif [[ "$handlers_lower" =~ kbd ]]; then
      if is_likely_keyboard "$name"; then
        echo "KEYBOARD"
      else
        echo "other"
      fi
    else
        echo "other"
    fi
}

quick_detect() {
  local show_all="$1"
  local prefer_byid="$2"   # "true" = prefer /dev/input/by-id symlinks
  local include_mouse_devices="$3"
  shift 3
  local ignore_devices=("$@")   # now receives array properly

  local devices
  devices=$(get_kbd_devices "${prefer_byid}" "${ignore_devices[@]}") || { error "Cannot read devices"; return 1; }

  if [[ -z "$devices" ]]; then
    warn "No input devices found"
    return 1
  fi

  echo
  echo -e "${BOLD}🐱 Bongo Cat Device Discovery${NC} v$VERSION"

  header "Detected Devices"

  local keyboards=()
  local mouses=()
  local others=()
  local config_devices=()
  local type=""

  while IFS='|' read -r event name handlers capabilities device_path; do
    local status="ok"
    check_device "/dev/input/$event" || status="denied"
    type=$(get_device_type "${name}" "${handlers}" "${capabilities}")

    if is_likely_mouse "$name"; then
      if [[ "$include_mouse_devices" == "true" ]]; then
        echo -e "  ${GREEN}✓${NC} ${GREEN}[$type]${NC} ${BOLD}$name${NC}"
        config_devices+=("$event|$name|$device_path")
      else
        echo -e "  ${DIM}○ [$type]    $name${NC}"
        if [[ "$show_all" == "true" ]]; then
          config_devices+=("$event|$name|$device_path")
        fi
      fi
      mouses+=("$event|$name")
    elif is_likely_keyboard "$name"; then
      echo -e "  ${GREEN}✓${NC} ${GREEN}[$type]${NC} ${BOLD}$name${NC}"
      keyboards+=("$event|$name|$device_path")
      config_devices+=("$event|$name|$device_path")
    else
      echo -e "  ${DIM}○ [$type]    $name${NC}"
      others+=("$event|$name")
      if [[ "$show_all" == "true" ]]; then
        config_devices+=("$event|$name|$device_path")
      fi
    fi
    echo -e "    ${CYAN}/dev/input/$event${NC}"
  done <<< "$devices"

  if [[ ${#keyboards[@]} -eq 0 ]]; then
    echo
    warn "Could not auto-detect keyboards by name"
    info "Use interactive mode: ${CYAN}$SCRIPT_NAME --interactive${NC}"
    return 1
  fi

  # Config suggestion
  header "Add to Config"
  echo -e "  ${BOLD}~/.config/bongocat/bongocat.conf:${NC}"
  echo
  generate_config "${config_devices[@]}"

  echo
  echo -e "  ${DIM}Not accurate? Use: $SCRIPT_NAME --interactive${NC}"
  echo
}

quick_config() {
  local show_all="$1"
  local prefer_byid="$2"   # "true" = prefer /dev/input/by-id symlinks
  local include_mouse_devices="$3"
  shift 3
  local ignore_devices=("$@")   # now receives array properly

  local devices
  devices=$(get_kbd_devices "${prefer_byid}" "${ignore_devices[@]}") || { error "Cannot read devices"; return 1; }

  if [[ -z "$devices" ]]; then
    return 1
  fi

  local keyboards=()
  local mouses=()
  local others=()
  local config_devices=()

  while IFS='|' read -r event name handlers capabilities device_path; do
    local status="ok"
    check_device "/dev/input/$event" || status="denied"
    local type
    type=$(get_device_type "${name}" "${handlers}" "${capabilities}")

    if is_likely_mouse "$name"; then
      if [[ "$include_mouse_devices" == "true" ]]; then
        config_devices+=("$event|$name|$device_path")
      else
        if [[ "$show_all" == "true" ]]; then
          config_devices+=("$event|$name|$device_path")
        fi
      fi
      mouses+=("$event|$name|$device_path")
    elif is_likely_keyboard "$name"; then
      keyboards+=("$event|$name|$device_path")
      config_devices+=("$event|$name|$device_path")
    else
      others+=("$event|$name|$device_path")
      if [[ "$show_all" == "true" ]]; then
        config_devices+=("$event|$name|$device_path")
      fi
    fi
  done <<< "$devices"

  if [[ ${#keyboards[@]} -eq 0 ]]; then
    return 1
  fi

  # Config suggestion
  generate_config "${config_devices[@]}"
}

# ─────────────────────────────────────────────────────────────────────────────
# Main
# ─────────────────────────────────────────────────────────────────────────────

show_usage() {
  cat << EOF
${BOLD}$SCRIPT_NAME${NC} v$VERSION - Find keyboards for Bongo Cat

${BOLD}USAGE${NC}
    $SCRIPT_NAME [OPTIONS]

${BOLD}OPTIONS${NC}
        --all                     Show all input devices (including mice, touchpads)
        --by-id                   Show input devices as id (symlink, if available)
        --ignore-device PATTERN   Ignore device (multiple arguments)
        --include-mouse           Include Mouse Device in config
    -i, --interactive             Detect keyboards by listening for key presses (recommended)
    -t, --timeout SEC             Detection timeout in seconds (default: 5)
    -g, --generate                Output config lines only (for piping)
    -h, --help                    Show this help

${BOLD}EXAMPLES${NC}
    $SCRIPT_NAME                                    # Quick detection (name-based)
    $SCRIPT_NAME -i                                 # Interactive detection (recommended)
    $SCRIPT_NAME -i -t 10                           # Interactive with 10 second timeout
    $SCRIPT_NAME --generate > bongocat.conf         # Generate config file

    { cat bongocat.conf.example; "$SCRIPT_NAME" --generate --devices-only; } > bongocat.conf
EOF
}

main() {
  local mode="quick"
  local timeout=5
  local show_all=false
  local prefer_byid=false
  local include_mouse_devices=false
  local ignore_devices=()

  while [[ $# -gt 0 ]]; do
    case "$1" in
      --all) show_all=true; shift ;;
      --by-id) prefer_byid=true; shift ;;
      --include-mouse) include_mouse_devices=true; shift ;;
      --ignore-device)
        if [[ -n "$2" ]]; then
          ignore_devices+=("$2")
          shift 2
        else
          echo "Error: --ignore-device requires a value" >&2
          exit 1
        fi
        ;;
      -i|--interactive) mode="interactive"; shift ;;
      -t|--timeout) timeout="$2"; shift 2 ;;
      -g|--generate) mode="generate"; shift ;;
      --generate-config) mode="generate"; shift ;;
      -h|--help) show_usage; exit 0 ;;
      *) error "Unknown option: $1"; show_usage; exit 1 ;;
    esac
  done

  case "$mode" in
    interactive) interactive_detect "$timeout" "$prefer_byid" ;;
    quick) quick_detect "$show_all" "$prefer_byid" "$include_mouse_devices" "${ignore_devices[@]}" ;;
    generate) quick_config "$show_all" "$prefer_byid" "$include_mouse_devices" "${ignore_devices[@]}" ;;
  esac
}

main "$@"