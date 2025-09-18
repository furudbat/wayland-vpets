{
  lib,
  stdenv,
  pkg-config,
  wayland,
  wayland-protocols,
  wayland-scanner,
  cmake
}:
stdenv.mkDerivation (finalAttrs: {
  pname = "wayland-vpets";
  version = "3.0.1";
  src = ../.;

  # Build toolchain and dependencies
  strictDeps = true;
  nativeBuildInputs = [pkg-config wayland-scanner];
  buildInputs = [
    wayland
    wayland-protocols
  ];

  # Build phases
  # Ensure that the Makefile has the correct directory with the Wayland protocols
  preBuild = ''
    export WAYLAND_PROTOCOLS_DIR="${wayland-protocols}/share/wayland-protocols"
  '';

  makeFlags = ["release"];
  installPhase = ''
    runHook preInstall

    # Install binaries
    install -Dm755 build/bongocat $out/bin/${finalAttrs.meta.mainProgram}
    install -Dm755 scripts/find_input_devices.sh $out/bin/bongocat-find-devices

    runHook postInstall
  '';

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
