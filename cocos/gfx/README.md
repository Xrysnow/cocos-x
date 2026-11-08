# cocos-x gfx

This is the low-level graphics module of cocos-x, ported from [cocos4](https://github.com/cocos/cocos4). Its sources are maintained directly in `cocos/gfx`, with the original gfx repository history merged into cocos-x. It is not a submodule.

The cocos renderer adapter remains in `cocos/renderer/backend/gfx`.

### Dependencies

- taskflow
- glslang
- spirv-cross
- PVRVFrame libraries (for GLES backend on Windows)

### CMake usage

`cocos/CMakeLists.txt` builds this module as the independent C++20 static library `cocos_gfx` and links it directly to `cocos2d`. Shader compiler and optional job-system dependencies are supplied by the engine's `external` directory. Metal header and framework requirements are configured by this module.
