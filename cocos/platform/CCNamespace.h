#pragma once

#ifdef __cplusplus
namespace cc {}
namespace cocos2d = cc;
#endif

/// @name namespace cc
/// @{
#ifdef __cplusplus
    #define NS_CC_BEGIN                     namespace cc {
    #define NS_CC_END                       }
    #define USING_NS_CC                     using namespace cc
    #define NS_CC                           ::cc
#else
    #define NS_CC_BEGIN
    #define NS_CC_END
    #define USING_NS_CC
    #define NS_CC
#endif
//  end of namespace group
/// @}
