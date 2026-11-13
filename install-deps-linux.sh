#!/usr/bin/env bash
set -euo pipefail

# Debian/Ubuntu host tools and system interfaces only. OpenSSL, curl, OpenAL,
# GLFW and PNG are built from bundled sources; zlib uses the bundled library.
# Linux deliberately uses system FreeType (2.11 or newer).
if ! command -v apt-get >/dev/null 2>&1; then
    echo "This script requires apt-get (Debian/Ubuntu)." >&2
    exit 1
fi

packages=(
    # Compiler, build tools and configure-time dependency builders.
    build-essential ninja-build pkg-config binutils perl git
    # X11 / XCB and OpenGL.
    libxxf86vm-dev libx11-dev libxrandr-dev libxinerama-dev
    libxcursor-dev libxi-dev libxext-dev libxcb1-dev libgl1-mesa-dev
    # GLFW enables both X11 and Wayland by default.
    libwayland-dev libwayland-bin libxkbcommon-dev
    # OpenAL audio backends.
    libasound2-dev libpulse-dev
    # Text input and fonts.
    libgtk-3-dev libfontconfig1-dev libfreetype6-dev
)

printf 'Install build tools and system development packages:\n'
printf '  %s\n' "${packages[@]}"
printf 'Continue? [y/N] '
if ! read -r answer || [[ ! "$answer" =~ ^[Yy]([Ee][Ss])?$ ]]; then
    echo "Cancelled."
    exit 0
fi

privilege=()
if (( EUID != 0 )); then
    if ! command -v sudo >/dev/null 2>&1; then
        echo "Run as root or install sudo to install these packages." >&2
        exit 1
    fi
    privilege=(sudo)
fi

"${privilege[@]}" apt-get update
"${privilege[@]}" apt-get install --yes "${packages[@]}"

echo "System dependencies are ready."
echo "Ensure the system FreeType development package is 2.11 or newer. CMake checks this requirement."
echo "Select CMake 3.28+ and a compiler with the required C++20 library support before configuring."
echo "CMake, platform SDKs and Live2D Cubism Core are not installed by this script."
