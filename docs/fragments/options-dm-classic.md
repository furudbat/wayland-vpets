      -h, --help
            Show this help message

      -v, --version
            Show version information

      -c, --config FILE
            Specify config file (default: $XDG_CONFIG_HOME/bongocat/bongocat.conf,
            ~/.config/bongocat/bongocat.conf or ./bongocat.conf)
            Use "-" to read the configuration from standard input.

      -w, --watch-config
            Watch config file for changes and reload automatically

      -t, --toggle
            Toggle bongocat on/off (start if not running, stop if running)

      -o, --output-name NAME
            Specify output name (overrides monitor from config)

      -m, --monitor NAME
            Bind to a specific monitor output (same as --output-name)

          --random
            Enable random animation_index at start (overrides random from config)

          --strict
            Enable strict mode, only start with a valid config and valid parameters

          --nr NR
            Specify Nr. for PID file to avoid conflicting with running instances

          --ignore-running
            Ignore current running instance

          --debug
            Override enable_debug setting

          --check-config
            Strictly validate the configuration

          --list-devices
            List input devices and keyboard settings

          --list-monitors
            List Wayland outputs, sizes and scales

          --doctor
            Check configuration, devices and compositor support

          --list-devices-config
            List input devices and keyboard settings in config format

          --default-devices
            Load every keyboard by default, when no keyboard was found in config

Included sets:

      bongocat - Classic Bongo cat
            dm - Digital Monster Original
          dm20 - Digital Monster Ver.20th
           dmx - Digital Monster X
           pen - Digimon Pendulum
         pen20 - Digimon Pendulum Ver.20th
