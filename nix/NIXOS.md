# NixOS Installation Guide

> [!WARNING]
> This guide may contain misinformation, please open a PR with the changes if you find something wrong

## Quick Start

### Direct Installation with Flakes

```bash
# Try `wayland-bongocat` without installing
nix run github:furudbat/wayland-vpets

# Install to user profile
nix profile install github:furudbat/wayland-vpets

# Find your input devices
bongocat-find-devices
```

### Using the NixOS Module (Recommended)

Remember to rebuild your system!

#### With Flakes (Recommended)

If you use flakes for your NixOS configuration (Which you should):

```nix
# In your `flake.nix`
{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    bongocat.url = "github:furudbat/wayland-vpets";
  };

  outputs = inputs: {
    nixosConfigurations.your-hostname = inputs.nixpkgs.lib.nixosSystem {
      system = "x86_64-linux";
      modules = [
        ./configuration.nix
        inputs.bongocat.nixosModules.default
        {
          programs.wayland-bongocat = {
            enable = true;
            autostart = true;
          };
        }
      ];
    };
  };
}
```

#### Without Flakes

Download this repository wherever you desire and add this to your NixOS configuration:

```nix
{ config, pkgs, ... }: {
  # Import the module
  imports = [
    # ... your other imports
    /path/to/wayland-bongocat/nix/nixos-module.nix
  ];

  # Enable and configure bongocat
  programs.wayland-bongocat = {
    enable = true;
    autostart = true;            # Start on login by creating a SystemD service

    executable = "bongocat-all"; # `bongocat` only contains the cat; -dm, -pkmn, -ms-agent, -all contain the v-pets
    animationName = "Agumon";    # Pet, see `man 5 bongocat-all` for all names

    # Position and size (in pixels)
    catXOffset = 120;
    catYOffset = 0;
    catHeight = 40;
    overlayHeight = 60;
    overlayOpacity = 0;          # Transparent overlay bar

    # Keyboards: with no devices/names set, every keyboard is used (defaultDevices)
    # Find yours with `bongocat --list-devices` or `bongocat-find-devices`
    # inputDeviceNames = [ "KW75 Keyboard" ];
  };
}
```

### Using the Home Manager Module

A home manager module is also provided by the repository flake. It's just like the NixOS module, but for home-manager!

```nix
# In your `flake.nix`
{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    home-manager = {
      url = "github:nix-community/home-manager";
      inputs.nixpkgs.follows = "nixpkgs";
    };
    bongocat.url = "github:furudbat/wayland-vpets";
  };

  outputs = inputs: {
    homeConfigurations.user = inputs.home-manager.lib.homeManagerConfiguration {
      # ...
      modules = [
        inputs.bongocat.homeModule.default
        # ...
      ];
    };
  };
}
```

## Options

All options live under `programs.wayland-bongocat`.
Settings are only written to the generated `bongocat.conf` when they are set, otherwise the binary default applies
(see `bongocat.conf.example` and `man 5 bongocat`).

| Option | Description |
| --- | --- |
| `enable` | Install `bongocat` and the `bongocat-exec` helper, which runs it with the generated config. |
| `autostart` | Run bongocat as the systemd user service `wayland-bongocat`, bound to `graphical-session.target`. |
| `package` | Package to use. |
| `executable` | Binary inside the package to run (default `bongocat`). |
| `monitor` | Output name, empty selects the output automatically (`bongocat --list-monitors`). |
| `inputDevices` | Input device paths (`keyboard_device`). |
| `inputDeviceNames` | Input device names (`keyboard_name`). |
| `defaultDevices` | Use every keyboard when no configured device is found (`--default-devices`, default `true`). |
| `extraConfig` | Raw lines appended to `bongocat.conf`, e.g. the `custom_*` sprite sheet settings. |

Settings (config key in brackets):

- **Pet:** `animationName` (`animation_name`), `animationIndex`, `random`, `randomOnReload`, `evolution` (`none`, `normal`, `program`, `uptime`), `evolutionSpeedFactor`
- **Overlay:** `overlayHeight`, `overlayPosition`, `overlayLayer` (`overlay_layer`, `layer` is a renamed alias), `overlayOpacity`, `disableFullscreenHide`
- **Position/size:** `catHeight`, `catXOffset`, `catYOffset`, `catAlign`, `paddingX`, `paddingY`, `screenWidth`
- **Visual:** `mirrorX`, `mirrorY`, `enableAntialiasing`, `invertColor`
- **Animation:** `idleFrame`, `idleAnimation`, `animationSpeed`, `keypressDuration`, `testAnimationDuration`, `testAnimationInterval`, `happyKpm`, `fps`, `inputFps`, `enableHandMapping`
- **Movement:** `movementRadius`, `movementSpeed`, `movementWaitFactor`, `enableMovementDebug`
- **CPU:** `updateRate`, `cpuThreshold`, `cpuRunningFactor`
- **Sleep:** `enableScheduledSleep`, `sleepBegin`, `sleepEnd` (`HH:MM`), `idleSleepTimeout`
- **Misc:** `hotplugScanInterval` (seconds), `enableDebug`

> [!NOTE]
> Since 6.0.0 the module no longer writes every option with its own defaults (and no hard-coded `/dev/input/event4`).
> Only the options you set end up in the config.

### Man pages

The package has a separate `man` output (`bongocat(1)`, `bongocat(5)`, `bongocat-all(1)`, `bongocat-all(5)`, ...,
`bongocat-find-devices(1)`), installed automatically when man pages are enabled
(`documentation.man.enable` on NixOS, `programs.man.enable` in Home Manager, both on by default).

```bash
man bongocat-all     # usage
man 5 bongocat-all   # config, incl. all animation names
```

## Developing

### Using Flakes (RECOMMENDED)

Just enter the development environment with the `nix develop` command and build the project
with `nix build`. This command has to be executed in the same directory as the `flake.nix`
file.

The build output will be stored in `result/` with the binaries in `result/bin` in the
current directory.

`nix flake check` builds the package, checks the man pages (`man` output) and the config generated by the NixOS and Home Manager modules.
Without Nix installed, run `./scripts/tests/test_nix_build_docker.sh`.

## Configuration

Run `bongocat --list-devices` or `bongocat-find-devices` to find all input devices.

### Manual Configuration

Create a `bongocat.conf` file wherever you desire (see `bongocat.conf.example`):

```ini
animation_name=Agumon

# Input devices (or keyboard_name=..., or start with --default-devices)
keyboard_device=/dev/input/event4   # Built-in keyboard
keyboard_device=/dev/input/event20  # External keyboard

# Position and size
cat_x_offset=120
cat_y_offset=0
cat_height=40
overlay_height=60

# Visual settings
overlay_opacity=0  # Transparent background
```

## SystemD Service Management

Set `programs.wayland-bongocat.autostart = true;` to create a SystemD user service so
it gets automatically started upon login.

```bash
# Check service status
systemctl --user status wayland-bongocat

# Start/stop manually
systemctl --user start wayland-bongocat
systemctl --user stop wayland-bongocat

# View logs
journalctl --user -u wayland-bongocat -f
```

## Troubleshooting

### Permission Issues

If you get permission errors accessing input devices:

1. **Check if you're in the input group:** Run `groups | grep input`
2. **Add yourself to the `input` group:** Add to your configuration `users.users.<your username>.extraGroups = ["input"];`
3. **Log out and log back in after you add yourself to the `input` group**

### Service Issues

If the SystemD service fails to start:

1. **Check logs:** `journalctl --user -u wayland-bongocat -n 50`
1. **Test manually:** `bongocat --config /nix/store/.../bongocat.conf`
1. **Enable debug mode:** `programs.wayland-bongocat.enableDebug = true;`

### Input Device Detection

If keyboard input isn't detected:

1. **Find your devices:** `bongocat-find-devices`
2. **Test device events:** `sudo evtest  # Select your device and type`
3. **Update your configuration:**
   If using the NixOS or home-manager module -

   ```nix
   programs.wayland-bongocat.inputDevices = [
       # Add as many devices as required and replace X with your device number
       "/dev/input/eventX"
       "/dev/input/eventX"
       "/dev/input/eventX"
   ];
   ```

   Standalone (In your `bongocat.conf` file) -

   ```ini
   # Add as many devices as required and replace `X` with the actual device number
   keyboard_device=/dev/input/eventX
   keyboard_device=/dev/input/eventX
   keyboard_device=/dev/input/eventX
   ```

You can also use the recommended `keyboard_name=your keyboard` config suggestion provided by `bongocat-find-devices`.

In the NixOS or home-manager module -

```nix
programs.wayland-bongocat.inputDeviceNames = ["your keyboard"]
```

### Wayland Compositor Compatibility

Ensure your compositor supports the layer shell protocol:

- ✅ **Hyprland** - Full support
- ✅ **Sway** - Full support
- ✅ **Wayfire** - Compatible
- ✅ **KDE Wayland** - Compatible
- ❌ **GNOME Wayland** - Support Unknown

## Advanced Usage

### Custom Package

You can override the package in the module:

```nix
programs.wayland-bongocat = {
  enable = true;
  # the package contains all variants (bongocat, bongocat-all, bongocat-dm, bongocat-pkmn, bongocat-ms-agent, ...)
  executable = "bongocat-all";
  # or a custom build
  package = inputs.bongocat.packages.${pkgs.system}.default.overrideAttrs (old: {
    cmakeFlags = old.cmakeFlags ++ [ "-DFEATURE_EVOLUTION=OFF" ];
  });
};
```

### Multiple Configurations

You can run multiple instances using different configurations

```bash
# Instance 1
bongocat --config ~/.config/bongocat/work.conf &

# Instance 2
bongocat --config ~/.config/bongocat/gaming.conf &
```

### Integration with Window Managers

- **Hyprland:** `exec-once = bongocat`
- **Sway:** `exec bongocat`

## Building from Source

### Prerequisites

The flake includes all the necessary dependencies to build the project.
Just enter the development environment by running `nix develop` in the
same directory as the `flake.nix` file. The development environment will
provide further information e.g. commands to build the project.

> **Note:** The generated Wayland protocol bindings are committed to git (`protocols/`), so `wayland-scanner` is only needed in the dev shell for regenerating them. Regular builds (`cmake` / `nix build`) don't require it.

## Contributing

See the [README](../README.md) for contribution guidelines. The NixOS integration welcomes:

- Additional compositor testing
- Module option improvements
- Documentation enhancements
- Bug reports and fixes

## Support

For NixOS-specific issues:

1. Read through this guide thoroughly
2. Read through `nix/common.nix` (shared by the NixOS and Home Manager module)
3. Test with the development shell
4. Open an issue with your NixOS version and configuration