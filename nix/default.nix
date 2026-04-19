{
  lib,
  gcc15Stdenv,
  pkg-config,
  wayland,
  wayland-protocols,
  cmake,
  pandoc,
  libffi,
  systemd,
  libcap,
  libxkbcommon,
}:
gcc15Stdenv.mkDerivation (finalAttrs: {
  pname = "wayland-vpets";
  version = "4.0.0";
  src = ../.;

  # Build toolchain and dependencies
  # Protocol bindings are pre-generated and committed to git, so
  # wayland-scanner and wayland-protocols are only needed for `make protocols`.
  strictDeps = true;
  nativeBuildInputs = [pkg-config cmake pandoc];
  buildInputs = [
    wayland
    wayland-protocols
    libffi
    systemd
    libxkbcommon
    libcap
  ];

  cmakeFlags = [
    "-DCMAKE_BUILD_TYPE=Release"
    "-DSKIP_CPM=ON"
    "-DWAYLAND_PROTOCOLS_DIR=${wayland-protocols}/share/wayland-protocols"
    "-DCMAKE_INSTALL_PREFIX=$out"
  ];

  # Package information
  meta = {
    description = "Delightful Wayland overlay that displays an animated bongo cat and more vpets reacting to your keyboard input!";
    homepage = "https://github.com/furudbat/wayland-vpets";
    license = lib.licenses.mit;
    maintainers = with lib.maintainers; [voxi0 furudbat];
    mainProgram = "bongocat";
    platforms = lib.platforms.linux;
  };
})