# Standalone Windows x64 libraries

To include the cross-platform Lua application, configure the cocos-x root with
`-DCC_BUILD_DEMO=ON -DBUILD_LUA_LIBS=ON` and build the `cocos_demo` target.
The option defaults to `OFF` and works with both static and supported shared-core
builds. Platform entry points, icons and build commands are documented in
[`templates/README.md`](../templates/README.md).

The default `CC_BUILD_SHARED_LIBS=OFF` keeps the core and gfx static. Set
`CC_BUILD_SHARED_LIBS=ON` to build `cocos2d.dll` with gfx embedded in that DLL;
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
