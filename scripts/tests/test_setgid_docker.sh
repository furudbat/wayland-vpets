#!/usr/bin/env bash
##############################################################################
# test_setgid_docker.sh
#
# Tests keyboard access permissions in a container, with a real keyboard passed in
# read-only (owner/mode are only changed inside the container, the host is untouched):
#
#   1. not in input group, no setgid          -> must NOT open the keyboard
#   2. in input group (default setup)         -> must open the keyboard
#   3. not in input group, setgid bongocat    -> must open the keyboard
#      (README: "Alternative permissions setup", experimental)
#
# Builds the current working tree (incl. uncommitted changes) in Dockerfiles/archlinux-setgid.
# Needs a running Wayland session (the pet is shown for a few seconds per case).
# udev rules and the pacman hook are NOT tested here (no udev/pacman setup in the container).
#
# Usage (from the repo root):
#   scripts/tests/test_setgid_docker.sh [-d /dev/input/eventX] [-t SECONDS]
#
# Exit code: 0 = passed, 1 = failed
##############################################################################
set -euo pipefail

IMAGE="bongocat-test:archlinux-setgid"
DOCKERFILE="Dockerfiles/archlinux-setgid"

#-----------------------------------------------------------------------------
# inside the container (runs as root)
#-----------------------------------------------------------------------------
container_main() {
  : "${DEV:?}" "${HOST_UID:?}" "${WAYLAND_DISPLAY:?}"
  local timeout_sec="${RUN_TIMEOUT:-4}"
  local runtime_dir="/run/user/$HOST_UID"

  echo "== build: working tree"
  mkdir -p /work/src
  tar -C /src --exclude='./build' --exclude='./cmake-build-*' --exclude='./.git' -cf - . | tar -C /work/src -xf -
  cmake -S /work/src -B /work/build -DCMAKE_BUILD_TYPE=Debug -DSKIP_CPM=ON -DBUILD_TESTING=OFF \
    -DFEATURE_MULTI_VERSIONS=OFF -DGENERATE_PROTOCOLS=OFF -Wno-author > /dev/null
  cmake --build /work/build --target bongocat -j"$(nproc)" > /dev/null

  echo "== setup: user tester (uid $HOST_UID), groups input + bongocat"
  getent group input > /dev/null || groupadd --system input
  groupadd --system bongocat
  useradd -u "$HOST_UID" -M -N -s /bin/sh tester
  local tester_gid
  tester_gid="$(id -g tester)"
  mkdir -p "$runtime_dir"
  chown tester "$runtime_dir"
  chmod 700 "$runtime_dir"
  printf 'keyboard_device=%s\nenable_debug=1\n' "$DEV" > /tmp/test.conf
  chmod 644 /tmp/test.conf

  install -o root -g root -m 0755 /work/build/bongocat /usr/local/bin/wpets
  install -o root -g bongocat -m 2755 /work/build/bongocat /usr/local/bin/wpets-setgid

  # run <binary> <setpriv groups option> -> prints log, returns 0 if the keyboard was opened
  run() {
    local bin="$1" groups_opt="$2" log
    echo "   binary: $(stat -c '%A %U:%G' "/usr/local/bin/$bin") $bin"
    echo "   device: $(stat -c '%A %U:%G' "$DEV") $DEV"
    log=$(setpriv --reuid="$HOST_UID" --regid="$tester_gid" "$groups_opt" -- \
      env HOME=/tmp XDG_RUNTIME_DIR="$runtime_dir" WAYLAND_DISPLAY="$WAYLAND_DISPLAY" \
      sh -c "id; timeout $timeout_sec /usr/local/bin/$bin -c /tmp/test.conf --debug" 2>&1 || true)
    grep -E "^uid=|privilege_|Opened input device|Successfully opened|Failed to open|inaccessible|Permission denied|Failed to connect" \
      <<< "$log" | sed 's/^/   /' || true
    grep -q "Opened input device: $DEV" <<< "$log"
  }

  local failed=0
  check() { # <name> <expect: open|fail> <binary> <setpriv groups option>
    local name="$1" expect="$2" result
    echo
    echo "== $name (expect: $expect)"
    if run "$3" "$4"; then result=open; else result=fail; fi
    if [[ "$result" == "$expect" ]]; then
      echo "PASS: $name"
    else
      echo "FAIL: $name (got: $result)"
      failed=1
    fi
  }

  # default udev setup: root:input 0660
  chgrp input "$DEV"
  chmod 0660 "$DEV"
  check "1. not in input group, no setgid" fail wpets --clear-groups
  check "2. in input group" open wpets --groups=input

  # setgid setup: root:bongocat 0640 (README)
  chgrp bongocat "$DEV"
  chmod 0640 "$DEV"
  check "3. not in input group, setgid bongocat" open wpets-setgid --clear-groups

  echo
  if ((failed)); then
    echo "permission tests FAILED"
    return 1
  fi
  echo "permission tests passed"
}

if [[ "${1:-}" == "--container" ]]; then
  container_main
  exit $?
fi

#-----------------------------------------------------------------------------
# host
#-----------------------------------------------------------------------------
DEV="${DEV:-}"
RUN_TIMEOUT=4

usage() {
  sed -n '2,/^####/p' "$0" | sed 's/^# \{0,1\}//; /^#*$/d'
}

while (($#)); do
  case "$1" in
    -d | --device) DEV="$2"; shift 2 ;;
    -t | --timeout) RUN_TIMEOUT="$2"; shift 2 ;;
    -h | --help) usage; exit 0 ;;
    *) echo "Unknown argument: $1" >&2; usage >&2; exit 1 ;;
  esac
done

cd "$(git rev-parse --show-toplevel)"

if ! docker info > /dev/null 2>&1; then
  echo "Docker does not seem to be running. Please start Docker." >&2
  exit 1
fi
if [[ -z "${WAYLAND_DISPLAY:-}" || -z "${XDG_RUNTIME_DIR:-}" || ! -S "$XDG_RUNTIME_DIR/$WAYLAND_DISPLAY" ]]; then
  echo "No Wayland session found (WAYLAND_DISPLAY/XDG_RUNTIME_DIR)." >&2
  exit 1
fi

# default: first keyboard from /dev/input/by-id
if [[ -z "$DEV" ]]; then
  for link in /dev/input/by-id/*-event-kbd; do
    [[ -e "$link" ]] || continue
    DEV="$(readlink -f "$link")"
    echo "Using keyboard: $link -> $DEV"
    break
  done
fi
if [[ -z "$DEV" || ! -c "$DEV" ]]; then
  echo "No keyboard device found, use -d /dev/input/eventX (see: wpets-all --list-devices)" >&2
  exit 1
fi

echo "Building image $IMAGE ..."
docker build --rm -q -t "$IMAGE" - < "$DOCKERFILE" > /dev/null

echo "Running permission tests ..."
docker run --rm \
  -v "$PWD:/src:ro" \
  --device "$DEV:$DEV:r" \
  -v "$XDG_RUNTIME_DIR/$WAYLAND_DISPLAY:/run/user/$(id -u)/$WAYLAND_DISPLAY" \
  -e DEV="$DEV" \
  -e HOST_UID="$(id -u)" \
  -e WAYLAND_DISPLAY="$WAYLAND_DISPLAY" \
  -e RUN_TIMEOUT="$RUN_TIMEOUT" \
  "$IMAGE" bash /src/scripts/tests/test_setgid_docker.sh --container
