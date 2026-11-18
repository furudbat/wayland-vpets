#!/usr/bin/env bash
# Test script for Nix builds
set -euo pipefail

echo "🧪 Testing Nix builds for wayland-vpets"
echo "=========================================="

command -v nix >/dev/null || { echo "❌ Nix is required"; exit 1; }

SYSTEM=$(nix eval --impure --raw --expr builtins.currentSystem)
FLAKE_DIR=$(pwd)
fail() { echo "❌ $*" >&2; exit 1; }

# Evaluate everything (packages, modules, assertions) without building
echo "📦 Evaluating flake..."
nix flake check --no-build
echo "✅ Flake check (eval): SUCCESS"

# Default package (no audio module)
echo ""
echo "📦 Building default package..."
out=$(nix build --no-link --print-out-paths -L .#default.out)
"$out/bin/bongocat" --version || fail "bongocat --version"
for bin in bongocat bongocat-all bongocat-dm bongocat-dm-classic bongocat-ms-agent bongocat-pkmn bongocat-find-devices; do
  [ -x "$out/bin/$bin" ] || fail "missing binary $bin"
done
# runtime closure (stored first: `grep -q` + pipefail would fail on "Broken pipe")
closure=$(nix path-info -r "$out")
if grep -q pipewire <<<"$closure"; then
  echo "$closure"
  fail "default package should not depend on pipewire"
fi
echo "✅ Default package: SUCCESS"

# Man pages (separate `man` output)
echo ""
echo "📖 Checking man pages..."
man=$(nix build --no-link --print-out-paths .#default.man)
ls -R "$man/share/man"
for name in bongocat bongocat-all bongocat-dm bongocat-dm-classic bongocat-ms-agent bongocat-pkmn; do
  ls "$man/share/man/man1/$name.1"* >/dev/null || fail "missing man page $name(1)"
  ls "$man/share/man/man5/$name.conf.5"* >/dev/null || fail "missing man page $name.conf(5)"
done
ls "$man/share/man/man1/bongocat-find-devices.1"* >/dev/null || fail "missing man page bongocat-find-devices(1)"
echo "✅ Man pages: SUCCESS"

# Audio variant (PipeWire + FFTW)
echo ""
echo "🔊 Building package with audio module..."
audio_out=$(nix build --no-link --print-out-paths -L .#with-audio.out)
"$audio_out/bin/bongocat" --version || fail "bongocat (audio) --version"
audio_closure=$(nix path-info -r "$audio_out")
for dep in pipewire fftw; do
  if ! grep -q "$dep" <<<"$audio_closure"; then
    echo "$audio_closure"
    fail "audio package does not depend on $dep"
  fi
done
echo "✅ Audio package: SUCCESS"

# All flake checks (see `checks` in flake.nix), one by one for readable output
echo ""
echo "🧩 Running flake checks..."
for check in package package-audio manpages nixos-module home-module; do
  echo "  → $check"
  nix build --no-link -L ".#checks.$SYSTEM.$check" || fail "check $check"
done
echo "✅ Flake checks: SUCCESS"

# Module assertion: audio = true with a package built without the audio module must fail
echo ""
echo "🧩 Testing audio assertion of the NixOS module..."
if result=$(nix eval --impure --raw --expr "
  let
    f = builtins.getFlake \"path:$FLAKE_DIR\";
    sys = f.inputs.nixpkgs.lib.nixosSystem {
      system = \"$SYSTEM\";
      modules = [
        f.nixosModules.default
        {
          boot.isContainer = true;
          system.stateVersion = \"25.11\";
          programs.wayland-bongocat = {
            enable = true;
            audio = true;
            package = f.packages.$SYSTEM.default;
          };
        }
      ];
    };
  in sys.config.system.build.toplevel.drvPath" 2>&1); then
  fail "expected assertion failure, got: $result"
fi
grep -q "needs a package built with the audio module" <<<"$result" || fail "unexpected error: $result"
echo "✅ Audio assertion: SUCCESS"

# Development shell (incl. optional audio dependencies)
echo ""
echo "🔧 Testing development shell..."
nix develop --command true
nix develop --command pkg-config --exists libpipewire-0.3 fftw3 || fail "dev shell: libpipewire-0.3/fftw3 not found by pkg-config"
echo "✅ Development shell: SUCCESS"

echo ""
echo "🎉 All Nix builds completed successfully!"
echo ""
