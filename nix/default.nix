{
  lib,
  gcc15Stdenv,
  pkg-config,
  wayland,
  wayland-protocols,
  cmake,
  pandoc,
  systemd,
  libffi,
  libcap,
}:
gcc15Stdenv.mkDerivation (finalAttrs: {
  pname = "wayland-vpets";
  version = "6.0.0";
  src = ../.;

  # man pages go into their own output (installed by NixOS/Home Manager when man pages are enabled);
  # the cmake setup hook points CMAKE_INSTALL_MANDIR at $man/share/man
  outputs = ["out" "man"];

  # Build toolchain and dependencies
  # Protocol bindings are pre-generated and committed to git (protocols/), so wayland-scanner is not needed;
  # wayland-protocols is only used for its xdg-shell.xml (WAYLAND_PROTOCOLS_DIR).
  # pandoc builds the man pages.
  strictDeps = true;
  nativeBuildInputs = [pkg-config cmake pandoc];
  buildInputs = [
    wayland # wayland-client
    systemd # libudev
    # only for pkg-config
    libffi
    libcap
  ];

  cmakeFlags = [
    "-DCMAKE_BUILD_TYPE=Release"
    "-DSKIP_CPM=ON"
    "-DBONGOCAT_REQUIRE_MANPAGES=ON" # fail instead of silently skipping the man pages
    "-DWAYLAND_PROTOCOLS_DIR=${wayland-protocols}/share/wayland-protocols"
    # CMAKE_INSTALL_PREFIX is set to $out by the cmake setup hook
  ];

  # Package information
  meta = {
    description = "Delightful Wayland overlay that displays an animated bongo cat and other v-pets reacting to your keyboard input!";
    homepage = "https://github.com/furudbat/wayland-vpets";
    license = lib.licenses.mit;
    maintainers = [lib.maintainers.voxi0] ++ lib.optional (lib.maintainers ? furudbat) lib.maintainers.furudbat;
    mainProgram = "bongocat";
    platforms = lib.platforms.linux;
  };
})