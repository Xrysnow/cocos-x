/****************************************************************************
 Copyright (c) 2015-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 https://axmolengine.github.io/

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __PHYSICS_MESH_RENDERER_H__
#define __PHYSICS_MESH_RENDERER_H__

#include "base/ccConfig.h"
#include "3d/CCMeshRenderer.h"
#include "physics3d/CCPhysics3DObject.h"
#include "physics3d/CCPhysics3DComponent.h"

#if CC_USE_3D_PHYSICS

    #if (CC_ENABLE_BULLET_INTEGRATION)

NS_CC_BEGIN
/**
 * @addtogroup _3d
 * @{
 */

/**
 * @brief Convenient class to create a rigid body with a MeshRenderer
 */
class CC_DLL PhysicsMeshRenderer : public cocos2d::MeshRenderer
{
public:
    /** creates a PhysicsMeshRenderer */
    static PhysicsMeshRenderer* create(std::string_view modelPath,
                                   Physics3DRigidBodyDes* rigidDes,
                                   const cocos2d::Vec3& translateInPhysics = cocos2d::Vec3::ZERO,
                                   const cocos2d::Quaternion& rotInPhsyics = cocos2d::Quaternion::ZERO);

    /** creates a PhysicsMeshRenderer with a collider */
    static PhysicsMeshRenderer* createWithCollider(std::string_view modelPath,
                                               Physics3DColliderDes* colliderDes,
                                               const cocos2d::Vec3& translateInPhysics = cocos2d::Vec3::ZERO,
                                               const cocos2d::Quaternion& rotInPhsyics = cocos2d::Quaternion::ZERO);

    /** Get the Physics3DObject. */
    Physics3DObject* getPhysicsObj() const;

    /** Set synchronization flag, see Physics3DComponent. */
    void setSyncFlag(Physics3DComponent::PhysicsSyncFlag syncFlag);

    /** synchronize node transformation to physics. */
    void syncNodeToPhysics();

    /** synchronize physics transformation to node. */
    void syncPhysicsToNode();

    PhysicsMeshRenderer();
    virtual ~PhysicsMeshRenderer();

protected:
    Physics3DComponent* _physicsComponent;
};

// end of 3d group
/// @}
NS_CC_END

    #endif  // CC_ENABLE_BULLET_INTEGRATION

#endif  // CC_USE_3D_PHYSICS

#endif  // __PHYSICS_MESH_RENDERER_H__
