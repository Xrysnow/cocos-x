#include "ProgramStateRegistry.h"

CC_BACKEND_BEGIN

static ProgramStateRegistry* _sharedStateRegistry = nullptr;
/** returns the shared instance */
ProgramStateRegistry* ProgramStateRegistry::getInstance()
{
    if (_sharedStateRegistry)
        return _sharedStateRegistry;

    _sharedStateRegistry = cc::IntrusivePtr{new ProgramStateRegistry()}.detach();
    if (!_sharedStateRegistry->init())
    {
        CC_SAFE_RELEASE_NULL(_sharedStateRegistry);
    }

    return _sharedStateRegistry;
}

/** purges the cache. It releases the retained instance. */
void ProgramStateRegistry::destroyInstance()
{
    CC_SAFE_RELEASE_NULL(_sharedStateRegistry);
}

bool ProgramStateRegistry::init()
{
    return true;
}

void ProgramStateRegistry::registerProgram(uint32_t programType, int textureSamplerFlags, cc::IntrusivePtr<Program> program)
{
    uint32_t key = (programType << 16) | textureSamplerFlags;
    this->_registry.insert_or_assign(key, std::move(program));
}

void ProgramStateRegistry::clearPrograms()
{
    this->_registry.clear();
}

cc::IntrusivePtr<ProgramState> ProgramStateRegistry::newProgramState(uint32_t programType, int textureSamplerFlags)
{
    uint32_t key = ((programType) << 16) | textureSamplerFlags;
    auto it      = this->_registry.find(key);
    if (it != this->_registry.end())
    {
        auto* fallback = it->second.get();
        if (fallback)
            return cc::IntrusivePtr{new ProgramState(fallback)};
    }

    return cc::IntrusivePtr{new ProgramState(Program::getBuiltinProgram(programType))};
}

uint32_t ProgramStateRegistry::getProgramType(uint32_t programType, int textureSamplerFlags)
{
    uint32_t key = (static_cast<uint32_t>(programType) << 16) | textureSamplerFlags;
    auto it      = this->_registry.find(key);
    if (it != this->_registry.end())
    {
        auto* fallback = it->second.get();
        if (fallback)
            return fallback->getProgramType();
    }
    return programType;
}
// end of _backend group
/// @}
CC_BACKEND_END
