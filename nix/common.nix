# Shared implementation of the NixOS and Home Manager modules.
# `platform` is either "nixos" or "home-manager"; the result is a module.
platform:
{
  lib,
  config,
  pkgs,
  ...
}:
let
  cfg = config.programs.wayland-bongocat;
  types = lib.types;

  # Every setting defaults to null; null settings are not written to the
  # generated config, so the binary's built-in defaults apply
  # (see bongocat.conf.example and `man 5 bongocat`).
  setting =
    type: description:
    lib.mkOption {
      type = types.nullOr type;
      default = null;
      description = "${description} Unset uses the binary default.";
    };

  timeType = types.strMatching "([01][0-9]|2[0-3]):[0-5][0-9]";
  offsetType = types.ints.between (-16000) 16000;
  durationMsType = types.ints.between 0 60000;

  # Limits match the clamping in src/config/config.cpp.
  # name = [ configKey type description ]
  settings = {
    # Overlay
    overlayHeight = [ "overlay_height" (types.ints.between 16 2560) "Height of the overlay bar in pixels." ];
    overlayPosition = [ "overlay_position" (types.enum [ "top" "bottom" ]) "Screen edge the overlay is anchored to." ];
    overlayLayer = [ "overlay_layer" (types.enum [ "background" "bottom" "top" "overlay" ]) "Layer-shell layer of the overlay." ];
    overlayOpacity = [ "overlay_opacity" (types.ints.between 0 255) "Overlay background opacity, 0 is transparent." ];
    disableFullscreenHide = [ "disable_fullscreen_hide" types.bool "Keep the overlay visible over fullscreen windows." ];

    # Position and size
    catHeight = [ "cat_height" (types.ints.between 8 1024) "Height of the pet in pixels." ];
    catXOffset = [ "cat_x_offset" offsetType "Horizontal offset of the pet in pixels." ];
    catYOffset = [ "cat_y_offset" offsetType "Vertical offset of the pet in pixels." ];
    catAlign = [ "cat_align" (types.enum [ "left" "center" "right" ]) "Horizontal alignment of the pet." ];
    paddingX = [ "padding_x" (types.ints.between 0 16000) "Horizontal padding around every sprite frame in pixels." ];
    paddingY = [ "padding_y" (types.ints.between 0 16000) "Vertical padding around every sprite frame in pixels." ];
    screenWidth = [ "screen_width" (types.ints.between 0 16000) "Override the detected screen width, 0 detects it." ];

    # Visual
    mirrorX = [ "mirror_x" types.bool "Flip the pet horizontally." ];
    mirrorY = [ "mirror_y" types.bool "Flip the pet vertically." ];
    enableAntialiasing = [ "enable_antialiasing" types.bool "Smooth scaling using bilinear interpolation." ];
    invertColor = [ "invert_color" types.bool "Invert the sprite colors (dark mode)." ];

    # Pet
    animationName = [ "animation_name" types.str "Pet to show, e.g. \"bongocat\", a Digimon/Pokemon name, \"clippy\" or \"custom\" (the executable must contain that set, e.g. bongocat-all)." ];
    animationIndex = [ "animation_index" types.ints.unsigned "Pet index inside the selected set (alternative to animationName)." ];
    random = [ "random" types.bool "Pick a random pet on start." ];
    randomOnReload = [ "random_on_reload" types.bool "Pick a new random pet on config reload." ];
    evolution = [ "evolution" (types.enum [ "none" "normal" "program" "uptime" ]) "Evolution mode for V-Pets." ];
    evolutionSpeedFactor = [ "evolution_speed_factor" (types.numbers.between 0 5000) "Speed factor for evolution." ];

    # Animation
    idleFrame = [ "idle_frame" types.ints.unsigned "Frame shown while idle." ];
    idleAnimation = [ "idle_animation" types.bool "Enable the idle animation." ];
    animationSpeed = [ "animation_speed" durationMsType "Milliseconds per frame, 0 uses the fps speed." ];
    keypressDuration = [ "keypress_duration" durationMsType "Duration of the keypress animation in milliseconds." ];
    testAnimationDuration = [ "test_animation_duration" durationMsType "Duration of the test animation in milliseconds." ];
    testAnimationInterval = [ "test_animation_interval" types.ints.unsigned "Seconds between test animations, 0 disables them." ];
    happyKpm = [ "happy_kpm" (types.ints.between 0 10000) "Keystrokes per minute that trigger the happy animation, 0 disables it." ];
    fps = [ "fps" (types.ints.between 1 540) "Animation frame rate." ];
    inputFps = [ "input_fps" (types.ints.between 0 540) "Input thread frame rate, 0 uses fps." ];
    enableHandMapping = [ "enable_hand_mapping" types.bool "Map left/right keyboard halves to the left/right paw." ];

    # Movement
    movementRadius = [ "movement_radius" (types.ints.between 0 8000) "Moving area, the radius from center in pixels, 0 disables movement." ];
    movementSpeed = [ "movement_speed" durationMsType "Traveling distance per movement animation." ];
    movementWaitFactor = [ "movement_wait_factor" (types.numbers.nonnegative) "Wait time factor between movements." ];
    enableMovementDebug = [ "enable_movement_debug" types.bool "Show the movement area (in red)." ];

    # CPU
    updateRate = [ "update_rate" (types.ints.between 0 3600000) "CPU usage update rate in milliseconds, 0 disables it." ];
    cpuThreshold = [ "cpu_threshold" (types.numbers.between 0 100) "CPU usage (percent) that triggers the working animation." ];
    cpuRunningFactor = [ "cpu_running_factor" (types.numbers.between 0 50) "Speed-up factor for animationSpeed when the CPU reaches 100% usage, 0 disables it." ];

    # Sleep
    enableScheduledSleep = [ "enable_scheduled_sleep" types.bool "Sleep between sleepBegin and sleepEnd." ];
    sleepBegin = [ "sleep_begin" timeType "Scheduled sleep start time (HH:MM)." ];
    sleepEnd = [ "sleep_end" timeType "Scheduled sleep end time (HH:MM)." ];
    idleSleepTimeout = [ "idle_sleep_timeout" (types.ints.between 0 2592000) "Seconds without input before the pet sleeps, 0 disables it." ];

    # Input
    hotplugScanInterval = [ "hotplug_scan_interval" (types.ints.between 0 3600) "Seconds between input device rescans, 0 scans once." ];

    # Debug
    enableDebug = [ "enable_debug" types.bool "Enable debug logging." ];
  };

  renderValue = value: if builtins.isBool value then (if value then "1" else "0") else toString value;

  settingLines = lib.mapAttrsToList (name: spec: "${builtins.head spec}=${renderValue cfg.${name}}") (
    lib.filterAttrs (name: _: cfg.${name} != null) settings
  );

  configFile = pkgs.writeText "bongocat.conf" (
    lib.concatStringsSep "\n" (
      [ "# Generated by the wayland-bongocat Nix module" ]
      ++ settingLines
      ++ lib.optional (cfg.monitor != "") "monitor=${cfg.monitor}"
      ++ map (device: "keyboard_device=${device}") cfg.inputDevices
      ++ map (name: "keyboard_name=${name}") cfg.inputDeviceNames
      ++ lib.optional (cfg.extraConfig != "") cfg.extraConfig
    )
    + "\n"
  );

  execStart = lib.concatStringsSep " " (
    [
      "${cfg.package}/bin/${cfg.executable}"
      "--config"
      "${configFile}"
    ]
    ++ lib.optional cfg.defaultDevices "--default-devices"
  );

  # Starts bongocat with the config generated by this module.
  execScript = pkgs.writeShellScriptBin "bongocat-exec" "exec ${execStart}";

  description = "Wayland Bongo Cat Overlay";
  sessionTarget = "graphical-session.target";
  serviceConfig = {
    Type = "exec";
    ExecStart = execStart;
    Restart = "on-failure";
    RestartSec = "5s";
  };

  renamed =
    from: to:
    lib.mkRenamedOptionModule
      [
        "programs"
        "wayland-bongocat"
        from
      ]
      [
        "programs"
        "wayland-bongocat"
        to
      ];
in
{
  imports = [
    (renamed "layer" "overlayLayer")
  ];

  options.programs.wayland-bongocat =
    lib.mapAttrs (_: spec: setting (builtins.elemAt spec 1) (builtins.elemAt spec 2)) settings
    // {
      enable = lib.mkEnableOption "the wayland-bongocat overlay";

      autostart = lib.mkOption {
        type = types.bool;
        default = false;
        example = true;
        description = "Start bongocat on login through a systemd user service bound to graphical-session.target.";
      };

      package = lib.mkOption {
        type = types.package;
        default = pkgs.callPackage ./default.nix { };
        defaultText = lib.literalMD "the package built from this repository";
        description = "The wayland-bongocat package to use.";
      };

      executable = lib.mkOption {
        type = types.str;
        default = "bongocat";
        example = "bongocat-all";
        description = "Binary inside the package to run: bongocat, bongocat-all, bongocat-dm, bongocat-pkmn, bongocat-ms-agent, ...";
      };

      monitor = lib.mkOption {
        type = types.str;
        default = "";
        example = "eDP-1";
        description = "Output name to show the pet on. Empty selects the output automatically. Run `bongocat --list-monitors` to see the names.";
      };

      inputDevices = lib.mkOption {
        type = types.listOf types.str;
        default = [ ];
        example = [ "/dev/input/by-id/usb-Example_Keyboard-event-kbd" ];
        description = "Input device paths to monitor. Run `bongocat --list-devices` or `bongocat-find-devices` to see candidates.";
      };

      defaultDevices = lib.mkOption {
        type = types.bool;
        default = true;
        description = "Use every keyboard when neither inputDevices nor inputDeviceNames match a device (`--default-devices`).";
      };

      inputDeviceNames = lib.mkOption {
        type = types.listOf types.str;
        default = [ ];
        example = [ "KW75 Keyboard" ];
        description = "Input device names to monitor (keyboard_name). Run `bongocat --list-devices` to see candidates.";
      };

      extraConfig = lib.mkOption {
        type = types.lines;
        default = "";
        example = ''
          custom_sprite_sheet_filename=/path/to/sheet.png
          custom_idle_frames=2
        '';
        description = "Extra lines appended to bongocat.conf (e.g. custom_* sprite sheet settings). Do not repeat keys set through options.";
      };
    };

  # Internal: the generated config (used by the flake checks)
  options._bongocat = lib.mkOption {
    type = types.attrs;
    internal = true;
    visible = false;
    default = { };
  };

  config = lib.mkIf cfg.enable (
    {
      _bongocat = {
        inherit configFile;
      };
    }
    // (
      if platform == "nixos" then
        {
          environment.systemPackages = [
            cfg.package
            execScript
          ];
          systemd.user.services.wayland-bongocat = lib.mkIf cfg.autostart {
            inherit description serviceConfig;
            wantedBy = [ sessionTarget ];
            partOf = [ sessionTarget ];
            after = [ sessionTarget ];
          };
        }
      else
        {
          home.packages = [
            cfg.package
            execScript
          ];
          systemd.user.services.wayland-bongocat = lib.mkIf cfg.autostart {
            Unit = {
              Description = description;
              PartOf = [ sessionTarget ];
              After = [ sessionTarget ];
            };
            Install.WantedBy = [ sessionTarget ];
            Service = serviceConfig;
          };
        }
    )
  );
}
