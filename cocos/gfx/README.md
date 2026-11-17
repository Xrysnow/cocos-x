# cocos-x gfx

This is the low-level graphics module of cocos-x, ported from [cocos4](https://github.com/cocos/cocos4). Its sources are maintained directly in `cocos/gfx`, with the original gfx repository history merged into cocos-x. It is not a submodule.

The cocos renderer adapter remains in `cocos/renderer/backend/gfx`.

### Dependencies

- taskflow
- glslang
- spirv-cross
- PVRVFrame libraries (for GLES backend on Windows)

### CMake usage

`cocos/CMakeLists.txt` includes this module's source configuration and compiles gfx directly into `cocos2d` in both static and shared-core builds. The existing public include roots and backend definitions are preserved. Gfx translation units skip the core `cocos2d.h` precompiled header.

Shader compiler and optional job-system libraries are supplied by the engine's `external` target. Metal source properties and framework requirements are applied directly to the core target.
