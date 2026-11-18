# Nix/NixOS Support
## Files
- **`NIXOS.md`** - Comprehensive installation guide for Nix/NixOS users
- **`default.nix`** - Main package derivation
- **`nixos-module.nix`** - NixOS system module
- **`home-module.nix`** - Home Manager module
- **`common.nix`** - Shared implementation of both modules (options, generated config)
- **`shell.nix`** - Development environment
- **`scripts/tests/test_nix_build.sh`** - Test script for validating builds

## Quick Usage
Run these commands from the root directory of the project where `flake.nix` is.
```bash
# Enter development shell
nix develop

# Build
nix build

# Build with the audio module (PipeWire + FFTW)
nix build .#with-audio

# Build and run
nix run ./#default

# Test all Nix builds
./scripts/tests/test_nix_build.sh
```

See [NIXOS.md](NIXOS.md) for further information.