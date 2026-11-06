#!/usr/bin/env bash
# Test script for Nix builds
set -euo pipefail

echo "🧪 Testing Nix builds for wayland-vpets"
echo "=========================================="

command -v nix >/dev/null || { echo "❌ Nix is required"; exit 1; }

# Test flake build
echo "📦 Testing flake build..."
nix flake check --no-build
echo "✅ Flake check: SUCCESS"
nix build --no-link -L
echo "✅ Flake build: SUCCESS"

# Test NixOS + Home Manager modules (generated bongocat.conf, see `checks` in flake.nix)
echo ""
echo "🧩 Testing NixOS and Home Manager modules..."
nix flake check -L
echo "✅ Module checks: SUCCESS"

# Test development shell
echo ""
echo "🔧 Testing development shell..."
nix develop --command true
echo "✅ Development shell: SUCCESS"

echo ""
echo "🎉 All Nix builds completed successfully!"
echo ""