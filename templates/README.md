# cocos-x Lua demo

The demo shares `Classes/AppDelegate.*` and `Resources/main.lua` across Windows,
Linux, macOS, iOS and Android. Lua creates one `cc.Label` containing `Hello world!`
16 design units from the upper-left corner of the visible area. The desktop
window is 960 x 540. No console window or statistics overlay is created.
The script returns `true` after installing the scene so startup can detect a
missing or broken script. Desktop resource lookup also works from another CWD.

`CC_BUILD_DEMO` defaults to `OFF`. Enable it at the **cocos-x** CMake entry point;
`BUILD_LUA_LIBS=ON` is required. The application target is `cocos_demo`. There are
no generated projects or machine-specific SDK paths in this source directory.

## Windows

Run from the cocos-x root with CMake 3.28+ and the engine's existing dependencies
(including native Windows Perl and NASM):

```powershell
cmake -S . -B build-demo-win64 -G "Visual Studio 18 2026" -A x64 -DCC_BUILD_DEMO=ON
cmake --build build-demo-win64 --config Debug --target cocos_demo -- /m:1 /nr:false
```

Open `build-demo-win64/cocos-x.slnx` (or the solution produced by your generator).
The startup project is `cocos_demo`. Its executable, `Resources/`, required DLLs
and OpenSSL provider modules are deployed to `bin/cocos_demo/Debug/`. The target
uses the Windows GUI subsystem in every configuration; its icon is embedded in
the executable. `CC_BUILD_SHARED_LIBS=ON` also works with the supported Windows
x64 MSVC shared-core configuration; use a different build directory when changing
static/shared mode.

## Linux

Install the engine's Linux development dependencies first, then:

```sh
cmake -S . -B build-demo-linux -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCC_BUILD_DEMO=ON
cmake --build build-demo-linux --target cocos_demo
./build-demo-linux/bin/cocos_demo/cocos_demo
```

The PNG window icon and Lua script are copied to `Resources/` beside the binary.
Linked shared targets and their runtime modules are copied beside the executable;
the build RPATH includes `$ORIGIN`.
Resource deployment runs on every desktop build, including Lua-only edits.

## macOS

```sh
cmake -S . -B build-demo-mac -G Xcode -DCC_BUILD_DEMO=ON \
  -DCMAKE_OSX_ARCHITECTURES=arm64 -DCMAKE_OSX_DEPLOYMENT_TARGET=12.0
cmake --build build-demo-mac --config Debug --target cocos_demo
open build-demo-mac/bin/cocos_demo/Debug/cocos_demo.app
```

The bundle contains the Lua script, PNG and multi-resolution ICNS icon. No
console controller is used. Use the matching architecture for engine dependencies.

## iOS

```sh
cmake -S . -B build-demo-ios -G Xcode -DCMAKE_SYSTEM_NAME=iOS \
  -DCMAKE_OSX_SYSROOT=iphoneos -DCMAKE_OSX_ARCHITECTURES=arm64 \
  -DCMAKE_OSX_DEPLOYMENT_TARGET=17.0 -DCC_BUILD_DEMO=ON
```

Open the generated Xcode project, select `cocos_demo`, set your signing team and
choose a device. The iPhone/iPad target includes an AppIcon asset catalog and a
plain launch storyboard. UIKit owns the native gfx Metal surface and forwards
background/foreground events to the shared application. Simulator builds require
engine dependencies built for that simulator SDK.

## Android

Open `templates/proj.android` in Android Studio or run its Gradle wrapper with a
JDK 17+ and installed SDK 35, NDK `30.0.16248370`, and CMake `4.1.2`:

```sh
cd templates/proj.android
sh ./gradlew :app:assembleDebug
# Windows: .\gradlew.bat :app:assembleDebug
```

Set `sdk.dir` in the ignored `local.properties` or use `ANDROID_HOME`.
`PROP_APP_ABI` defaults to `arm64-v8a`; colon-separated ABIs are supported.
Gradle enables `CC_BUILD_DEMO=ON` and builds `libcocos_demo.so` through the root
cocos-x CMake project. JNI glue is retained with whole-archive linking; the
manifest library name matches the CMake target. The APK packages `Resources/`
directly as assets and uses generated mdpi through xxxhdpi launcher icons.
Native host-tool overrides such as `-PCC_OPENSSL_PERL=...` and
`-PCC_LUAJIT_MAKE=...` are forwarded to CMake, as in the engine build.
The Debug APK is at `app/build/outputs/apk/debug/app-debug.apk`.

## Icons

The icon originates from [cocos/cocos4](https://github.com/cocos/cocos4).
Windows contains 16–256 pixel ICO entries, macOS contains 16–1024 pixel ICNS
entries, iOS includes iPhone/iPad/App Store sizes, and Android includes all five
launcher densities. iOS icons are flattened onto white because App Store icons
must be opaque.
