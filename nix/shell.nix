{pkgs ? import <nixpkgs> {}}:
pkgs.mkShellNoCC {
  nativeBuildInputs = with pkgs; [
    # Build dependencies
    # Core
    pkg-config  # Finds build dependencies
    gcc         # C/C++ compiler and also for `make`
    clang
    cmake

    # Wayland
    wayland-scanner

    # Devtools
    gdb         # Debugger
    valgrind    # Memory debugger
    clang-tools # Useful tools for C/C++ including a formatter `clang-format`
    #cmake-format

    # Optional tools for input device debugging
    evtest
    udev
  ];
  buildInputs = with pkgs; [
    wayland
    wayland-protocols
  ];
  shellHook = ''
    export CC=clang
    export CXX=clang++
    export CMAKE_GENERATOR=Ninja

    echo "🐱 Bongo Cat Dev Shell"
    echo
    echo "Toolchain:"
    echo "  CC=$CC"
    echo "  CXX=$CXX"
    echo "  CMake=$(cmake --version | head -n1)"
    echo
    echo "Quick commands:"
    echo "  nix build           -> build via flake"
    echo "  cmake -B build      -> configure"
    echo "  cmake --build build"
    echo
    echo ""
    echo "Helper scripts:"
    echo "  ./scripts/find_input_devices.sh - Find input devices"
    echo "  ./scripts/test_nix_build.sh     - Test Nix flake and package"
    echo "  ./scripts/test_toggle.sh        - Test Bongocat toggle functionality (Install Bongocat first)"
  '';
}