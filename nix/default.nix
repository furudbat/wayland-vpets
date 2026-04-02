{
  lib,
  gcc15Stdenv,
  pkg-config,
  wayland,
  wayland-protocols,
  wayland-scanner,
  cmake,
  pandoc,
  libffi,
  systemd,
  libcap,
  libxkbcommon
}:
gcc15Stdenv.mkDerivation (finalAttrs: {
  pname = "wayland-vpets";
  version = "3.6.2";
  src = ../.;

  # Build toolchain and dependencies
  strictDeps = true;
  nativeBuildInputs = [pkg-config cmake wayland-scanner pandoc];
  buildInputs = [
    wayland
    wayland-protocols
    libffi
    systemd
    libxkbcommon
    libcap
  ];

  # Build phases
  # Ensure that the Makefile has the correct directory with the Wayland protocols
  preBuild = ''
    export WAYLAND_PROTOCOLS_DIR="${wayland-protocols}/share/wayland-protocols"
  '';

  postPatch = ''
    grep -rl "/usr/share/wayland-protocols" . | while read f; do
      substituteInPlace "$f" \
        --replace "/usr/share/wayland-protocols" "${wayland-protocols}/share/wayland-protocols"
    done
  '';

  cmakeFlags = [
    "-DCMAKE_BUILD_TYPE=Release"
    "-DSKIP_CPM=ON"
    "-DWAYLAND_PROTOCOLS_DIR=${wayland-protocols}/share/wayland-protocols"
    "-DCMAKE_INSTALL_PREFIX=$out"
  ];

  # Package information
  meta = {
    description = "Delightful Wayland overlay that displays an animated v-pet reacting to your keyboard input!";
    homepage = "https://github.com/furudbat/wayland-vpets";
    license = lib.licenses.mit;
    maintainers = with lib.maintainers; [voxi0 furudbat];
    mainProgram = "bongocat";
    platforms = lib.platforms.linux;
  };
})