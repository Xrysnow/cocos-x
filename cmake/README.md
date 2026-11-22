# Linux AppImage packaging

On native Linux with CMake 3.28 or newer, `CC_BUILD_APPIMAGE` registers the
application's `appimage-<target>` build target by default. Set
`-DCC_BUILD_APPIMAGE=OFF` to omit it. Build the target explicitly to produce
`<build>/packages/<config>/<target>-<architecture>.AppImage`. With an empty
single-config build type, the output uses `NoConfig`.

The packaging target looks for `linuxdeploy` and `appimagetool` on `PATH` when
invoked. Set `CC_APPIMAGE_LINUXDEPLOY` and `CC_APPIMAGE_APPIMAGETOOL` to use
specific executable paths. For a pinned Type 2 runtime, set
`CC_APPIMAGE_RUNTIME_FILE` to its local path. Without that
setting, `appimagetool` uses its default runtime selection. The packaging tools
can themselves be AppImages and run in extract-and-run mode.

With native packaging tools, make `patchelf`, `file`, `desktop-file-validate`,
and `mksquashfs` available on `PATH`. On Ubuntu the last two are provided by
`desktop-file-utils` and `squashfs-tools`.

The target assembles a fresh AppDir on every invocation. It resolves linked ELF
dependencies from the configured Linux build environment and preserves the app's
resource layout. Distribution compatibility follows the libraries and symbol
versions in the resulting package and the host graphics stack. Build on the
oldest supported distribution and test there before release.

# Standalone Windows x64 libraries

To include the cross-platform Lua application, configure the cocos-x root with
`-DCC_BUILD_DEMO=ON -DBUILD_LUA_LIBS=ON` and build the `cocos_demo` target.
The option defaults to `OFF` and works with both static and supported shared-core
builds. Platform entry points, icons and build commands are documented in
[`templates/README.md`](../templates/README.md).

Gfx sources are compiled directly into the core target. The default
`CC_BUILD_SHARED_LIBS=OFF` builds a static `cocos2d` library; set
`CC_BUILD_SHARED_LIBS=ON` to build `cocos2d.dll`;
Lua bindings and extensions remain static libraries. The shared mode currently
supports Windows x64 with MSVC only. It does not change third-party library types.

Run the following commands from the cocos-x repository root. CMake 3.28 or newer,
Visual Studio, native Windows Perl and NASM are required. Configure a separate
Debug build tree:

```powershell
cmake -S . -B build-shared-x64 -G "Visual Studio 18 2026" -A x64 `
  -DCMAKE_CONFIGURATION_TYPES=Debug -DCC_BUILD_SHARED_LIBS=ON `
  -DBUILD_LUA_LIBS=ON -DCC_ENABLE_VIDEO_TEXTURE=ON -DUSE_JOB_SYSTEM_TASKFLOW=ON
cmake --build build-shared-x64 --config Debug -- /m:1 /nr:false
```

The core DLL is written to `build-shared-x64/bin/Debug/cocos2d.dll`, and its
import library to `build-shared-x64/lib/Debug/cocos2d.lib`. Other static libraries
are in the same `lib/Debug` directory. Use `-DBUILD_LUA_LIBS=OFF` when Lua bindings
are not needed. Preserve the selected feature switches when rebuilding.

For the original static mode, use another build directory and the same command
with `-DCC_BUILD_SHARED_LIBS=OFF`. Do not reuse a build tree when switching modes.
Both modes retain the MSVC dynamic CRT (`/MDd` for Debug, `/MD` for Release).

A shared build generates a build-tree package at `build-shared-x64/CocosX` for
consumers configured separately from the engine:

```cmake
find_package(CocosX CONFIG REQUIRED)
add_executable(example main.cpp)
target_link_libraries(example PRIVATE CocosX::cocos2d)
# For Lua and the enabled static extensions instead:
# target_link_libraries(example PRIVATE CocosX::luacocos2d CocosX::extensions)
```

Configure the consumer with `-DCocosX_DIR=<absolute-engine-build-path>/CocosX`
and build Debug with a matching x64 MSVC configuration. The package imports
prebuilt files; it never adds the engine source tree to the consumer build.
Headers still refer to this source checkout, so this is not a relocatable SDK.
`CocosX_CONFIGURATION` selects the generated engine configuration and defaults
to Debug for multi-configuration consumers. Feature and import definitions come
from the package; consumers should not define core producer macros or `CC_STATIC`.

Deploy every path in `CocosX_RUNTIME_DLLS` next to the executable. The
`CocosX_RUNTIME_MODULES` list contains source/destination pairs for additional
runtime files, with destinations relative to the executable. OpenSSL uses
`no-module`, so its default and legacy providers are built into `libcrypto`
and require no separate provider files. Runtime DLL dependencies remain separate
from `cocos2d.dll`.
