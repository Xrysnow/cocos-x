#pragma once

namespace cc
{
enum class FontRasterMode
{
    Bitmap,
    Sdf,
    Msdf
};
enum class GlyphRenderPolicy
{
    Async,
    Synchronous
};
enum class GlyphStatus
{
    Pending,
    Ready,
    Cancelled,
    InvalidInput,
    FileNotFound,
    UnsupportedFont,
    UnsupportedColorFont,
    NotFileFont,
    TooLarge,
    CacheFull,
    Busy,
    DeviceUnavailable,
    RasterError,
    UploadError
};
}  // namespace cc
