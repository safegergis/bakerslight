with import <nixpkgs> {};
mkShell {
  nativeBuildInputs = [
    cmake
    ninja
    pkg-config
    clang
    sfml
    xorg.libX11
    xorg.libXrandr
    xorg.libXinerama
    xorg.libXcursor
    xorg.libXfixes
    xorg.libXdamage
    udev
    freetype
    openal
    libvorbis
    libogg
    flac
    libglvnd
    entt
  ];
}
