# FYX - Alpha Blood Blending Bug - NG
*By Seb263*

Fixes the blood decal issue on alpha blended meshes with a dynamic, standalone SKSE plugin. No ESP or manual patches required. This "NG" version is fully automatic, mod-compatible, and applies the fix at game launch for a seamless experience.

The mod is available at: [nexusmods.com](https://www.nexusmods.com/skyrimspecialedition/mods/149128)

## Requirements

- [CMake](https://cmake.org/)
  - Add this to your `PATH`
- [Vcpkg](https://github.com/microsoft/vcpkg)
  - Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg
- [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
  - Desktop development with C++

## User Requirements

- [Address Library for SKSE](https://www.nexusmods.com/skyrimspecialedition/mods/32444)
  - Needed for SSE/AE
- [VR Address Library for SKSEVR](https://www.nexusmods.com/skyrimspecialedition/mods/58101)
  - Needed for VR

## Register Visual Studio as a Generator

- Open `x64 Native Tools Command Prompt`
- Run `cmake`
- Close the cmd window

## Building

```
# to update submodules in /extern
git submodule update --init --recursive
# configure cmake
cmake --preset build-release-msvc-msvc
# build dll
cmake --build build --preset release-msvc-msvc
```
