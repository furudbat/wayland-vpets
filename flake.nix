{
  description = "Bongo Cat Wayland Overlay - A fun animated overlay that reacts to keyboard input";

  # Dependencies
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  # What to do after fetching all dependencies
  outputs = inputs:
    inputs.flake-utils.lib.eachDefaultSystem (
      system: let
        pkgs = inputs.nixpkgs.legacyPackages.${system};
        lib = inputs.nixpkgs.lib;
        bongocat = pkgs.callPackage ./nix/default.nix {};

        # module settings used by the checks
        testSettings = {
          enable = true;
          autostart = true;
          animationName = "Agumon";
          catHeight = 60;
          catXOffset = -20;
          mirrorX = true;
          enableAntialiasing = false;
          evolution = "uptime";
          cpuThreshold = 90;
          layer = "overlay";
          inputDeviceNames = ["KW75 Keyboard"];
          extraConfig = "custom_idle_frames=2";
        };

        # checks the generated bongocat.conf (only set options, fork keys)
        checkConfig = name: configFile: execStart:
          pkgs.runCommand name {} ''
            conf=${configFile}
            cat "$conf"
            echo "ExecStart: ${execStart}"
            case "${execStart}" in
              *"/bin/bongocat --config "*"bongocat.conf --default-devices") ;;
              *) echo "FAIL: unexpected ExecStart" >&2; exit 1 ;;
            esac
            fail() { echo "FAIL: $*" >&2; exit 1; }
            expect() { grep -qxF "$1" "$conf" || fail "missing line '$1'"; }
            expect 'animation_name=Agumon'
            expect 'cat_height=60'
            expect 'cat_x_offset=-20'
            expect 'mirror_x=1'
            expect 'enable_antialiasing=0'
            expect 'evolution=uptime'
            expect 'cpu_threshold=90'
            expect 'overlay_layer=overlay'
            expect 'keyboard_name=KW75 Keyboard'
            expect 'custom_idle_frames=2'
            # unset options are not written, no hard-coded keyboard device
            for key in layer keyboard_device fps monitor; do
              if grep -q "^$key=" "$conf"; then
                fail "unexpected key '$key'"
              fi
            done
            [ "$(grep -c '^cat_height=' "$conf")" = 1 ]
            touch $out
          '';

        nixosConfig =
          (lib.nixosSystem {
            inherit system;
            modules = [
              inputs.self.nixosModules.default
              {
                boot.isContainer = true;
                system.stateVersion = "25.11";
                programs.wayland-bongocat = testSettings;
              }
            ];
          }).config;

        # Home Manager is not an input: evaluate the module against minimal stand-ins of the options it sets
        homeConfig =
          (lib.evalModules {
            modules = [
              inputs.self.homeManagerModules.default
              {
                options.home.packages = lib.mkOption {
                  type = lib.types.listOf lib.types.package;
                  default = [];
                };
                options.systemd.user.services = lib.mkOption {
                  type = lib.types.attrsOf lib.types.anything;
                  default = {};
                };
                config = {
                  _module.args.pkgs = pkgs;
                  programs.wayland-bongocat = testSettings;
                };
              }
            ];
          }).config;
      in {
        formatter = pkgs.alejandra;
        packages.default = bongocat;
        devShells.default = import ./nix/shell.nix {
          inherit pkgs;
        };

        checks = {
          package = bongocat;
          # every installed binary has its man pages (pandoc + docs/include.lua), and they render
          manpages = pkgs.runCommand "manpages-check" {nativeBuildInputs = [pkgs.mandoc];} ''
            man=${bongocat.man}/share/man
            ls -R "$man"
            for page in man1/bongocat-find-devices.1; do
              ls "$man/$page"* >/dev/null
            done
            for bin in ${bongocat}/bin/bongocat*; do
              name=$(basename "$bin")
              [ "$name" = "bongocat-find-devices" ] && continue
              ls "$man/man1/$name.1"* >/dev/null
              ls "$man/man5/$name.5"* >/dev/null
              mandoc -T utf8 "$man/man1/$name.1"* >/dev/null
              mandoc -T utf8 "$man/man5/$name.5"* >/dev/null
            done
            touch $out
          '';
          nixos-module =
            checkConfig "nixos-module-config" nixosConfig._bongocat.configFile
            nixosConfig.systemd.user.services.wayland-bongocat.serviceConfig.ExecStart;
          home-module =
            checkConfig "home-module-config" homeConfig._bongocat.configFile
            homeConfig.systemd.user.services.wayland-bongocat.Service.ExecStart;
        };
      }
    )
    // {
      nixosModules.default = import ./nix/nixos-module.nix;
      homeManagerModules.default = import ./nix/home-module.nix;
      homeModule.default = import ./nix/home-module.nix;
    };
}
