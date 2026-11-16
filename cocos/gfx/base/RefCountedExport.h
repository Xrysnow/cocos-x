#pragma once

// The common ownership header must not import gfx's assertion, logging, or
// platform helper macros into cocos clients. Match the core DLL build contract.
#if defined(_WIN32) && !defined(CC_STATIC)
    #if defined(_USRDLL)
        #define CC_REF_API __declspec(dllexport)
    #else
        #define CC_REF_API __declspec(dllimport)
    #endif
#else
    #define CC_REF_API
#endif
