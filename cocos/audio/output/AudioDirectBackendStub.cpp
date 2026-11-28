#include "AudioDirectBackend.h"

namespace cc::audio::detail {

AudioResult<std::vector<DirectEndpoint>> enumeratePlatformEndpoints()
{
    return AudioOutputError::Unsupported;
}

AudioResult<std::unique_ptr<OutputStream>> openPlatformOutput(const DirectEndpoint&)
{
    return AudioOutputError::Unsupported;
}

AudioResult<std::unique_ptr<OutputStream>> openPlatformRealtimeOutput(const DirectEndpoint&)
{
    return AudioOutputError::Unsupported;
}

void shutdownPlatformOutput() noexcept {}

} // namespace cc::audio::detail
