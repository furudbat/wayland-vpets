% bongocat-find-devices(1)
%
% November 2026

# NAME
bongocat-find-devices - find keyboards and input devices for Bongo Cat

# SYNOPSIS
`bongocat-find-devices [options]`

# DESCRIPTION
This tool scans your system for input devices and provides configuration
suggestions for Bongo Cat. It identifies keyboards, checks
permissions, and generates ready-to-use configuration snippets.

# OPTIONS
            --all                     Show all input devices (including mice, touchpads)
            --by-id                   Show input devices as id (symlink, if available; default)
            --by-event                Show input devices as /dev/input/eventX
        -e, --ignore-device PATTERN   Ignore device (can be given multiple times)
            --include-mouse           Include mouse devices in config
        -i, --interactive             Detect keyboards by listening for key presses (recommended)
        -t, --timeout SEC             Detection timeout in seconds (default: 5)
        -g, --generate                Output config lines only (for piping)
        -h, --help                    Show this help message

## Monitor Detection

For multi-monitor setups, use these commands to find monitor names:

        * wlr-randr                    # List all monitors (recommended)
        * swaymsg -t get_outputs       # Sway compositor only
        * bongocat logs show detected monitors during startup


# USAGE

## Basic device discovery

```bash
bongocat-find-devices
```


## Show all devices

```bash
bongocat-find-devices --all
```

## Interactive detection (recommended)
Press keys on every keyboard you want to use

```bash
bongocat-find-devices -i -t 10
```

## Generate config lines

```bash
bongocat-find-devices --generate > devices.bongocat.conf
bongocat-find-devices --generate --include-mouse > devices.bongocat.conf
```

_`/dev/input/eventX` can be mapped to a different device at boot, `--by-id` (default) gives more consistent paths_

## Ignore devices

```bash
bongocat-find-devices --generate --all -e "Power Button" -e "Mic Consumer" > devices.bongocat.conf
```

## More Examples

```bash
bongocat-find-devices --include-mouse --ignore-device "FootSwitch" --ignore-device "OpenTabletDriver" --generate
bongocat-find-devices --all --ignore-device "Power Button" --ignore-device "FootSwitch" --ignore-device "OpenTabletDriver" --ignore-device "Sound" --ignore-device "Video"  --ignore-device "Speaker" --ignore-device "Mic Consumer"  --generate
```


```{.include}
fragments/files.md
fragments/copyright.md
```

# SEE ALSO
`bongocat(1)`, `bongocat-all(1)`, `bongocat.conf(5)`
