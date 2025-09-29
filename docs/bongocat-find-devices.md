% bongocat-find-devices(1)
% 
% September 2025

# NAME
Wayland Bongo Cat - Input Device Discovery

# SYNOPSIS
`bongocat-find-devices [options]`

# DESCRIPTION
This tool scans your system for input devices and provides configuration
suggestions for Wayland Bongo Cat. It identifies keyboards, checks
permissions, and generates ready-to-use configuration snippets.

# OPTIONS
        -a, --all              Show all input devices (including mice, touchpads)
        -i, --by-id            Show input devices as id (symlink, if available)
        -e, --ignore-device    Ignore device (multiple arguments)
        -g, --generate-config  Generate configuration file to stdout
        -d, --devices-only     Print Input devices only (when generating configuration)
        -m, --include-mouse    Include Mouse Device in config
        -t, --test             Test device responsiveness (requires root)
        -v, --verbose          Show detailed device information
        -h, --help             Show this help message

## Monitor Detection

For multi-monitor setups, use these commands to find monitor names:

        * wlr-randr                    # List all monitors (recommended)
        * swaymsg -t get_outputs       # Sway compositor only
        * bongocat logs show detected monitors during startup


# USAGE

## Basic device discover

```bash
bongocat-find-devices
```


## Comprehensive device analysis

```bash
bongocat-find-devices --all --verbose
```

## Generate config file

```bash
bongocat-find-devices --generate-config > bongocat.conf
```

## Generate config file for devices only

```bash
bongocat-find-devices --generate-config --by-id --devices-only > devices.bongocat.conf
```

_`/dev/input/eventX` can be mapped to a different device at boot, use `--by-id` for more coherent paths and consistency_

## Ignore devices

```bash
bongocat-find-devices --generate-config -a --by-id --devices-only -e "Power Button" -e "Mic Consumer" > devices.bongocat.conf
```

```{.include}
fragments/files.md
fragments/copyright.md
```

# SEE ALSO
bongocat(1), bongocat.conf(5)