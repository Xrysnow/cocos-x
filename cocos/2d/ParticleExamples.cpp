/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2016 Chukong Technologies Inc.
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

#include "2d/ParticleExamples.h"
#include "base/Director.h"
#include "base/firePngData.h"
#include "renderer/TextureCache.h"

NS_CC_BEGIN
//
// ParticleFire
//

static Texture2D* getDefaultTexture()
{
    Texture2D* texture = nullptr;
    Image* image       = nullptr;
    do
    {
        const std::string key = "/__firePngData";
        texture               = Director::getInstance()->getTextureCache()->getTextureForKey(key);
        CC_BREAK_IF(texture != nullptr);

        image    = cc::IntrusivePtr{new Image()}.detach();
        bool ret = image->initWithImageData(__firePngData, sizeof(__firePngData));
        CC_BREAK_IF(!ret);

        texture = Director::getInstance()->getTextureCache()->addImage(image, key);
    } while (0);

    CC_SAFE_RELEASE(image);

    return texture;
}

cc::IntrusivePtr<ParticleFire> ParticleFire::create()
{
    cc::IntrusivePtr ret{new ParticleFire()};
    if (!(ret->init()))
    {
        return nullptr;
    }
    return ret;
}

cc::IntrusivePtr<ParticleFire> ParticleFire::createWithTotalParticles(int numberOfParticles)
{
    cc::IntrusivePtr ret{new ParticleFire()};
    if (!(ret->initWithTotalParticles(numberOfParticles)))
    {
        return nullptr;
    }
    return ret;
}

bool ParticleFire::initWithTotalParticles(int numberOfParticles)
{
    if (ParticleSystemQuad::initWithTotalParticles(numberOfParticles))
    {
        // duration
        _duration = DURATION_INFINITY;

        // Gravity Mode
        this->_emitterMode = Mode::GRAVITY;

        // Gravity Mode: gravity
        this->modeA.gravity.setZero();

        // Gravity Mode: radial acceleration
        this->modeA.radialAccel    = 0;
        this->modeA.radialAccelVar = 0;

        // Gravity Mode: speed of particles
        this->modeA.speed    = 60;
        this->modeA.speedVar = 20;

        // starting angle
        _angle    = 90;
        _angleVar = 10;

        // emitter position
        Vec2 winSize = _director->getWinSize();
        this->setPosition(winSize.width / 2.0f, 60.0f);
        this->_posVar.set(40.0f, 20.0f);

        // life of particles
        _life    = 3;
        _lifeVar = 0.25f;

        // size, in pixels
        _startSize    = 54.0f;
        _startSizeVar = 10.0f;
        _endSize      = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per frame
        _emissionRate = _totalParticles / _life;

        // color of particles
        _startColor.r    = 0.76f;
        _startColor.g    = 0.25f;
        _startColor.b    = 0.12f;
        _startColor.a    = 1.0f;
        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.0f;
        _startColorVar.a = 0.0f;
        _endColor.r      = 0.0f;
        _endColor.g      = 0.0f;
        _endColor.b      = 0.0f;
        _endColor.a      = 1.0f;
        _endColorVar.r   = 0.0f;
        _endColorVar.g   = 0.0f;
        _endColorVar.b   = 0.0f;
        _endColorVar.a   = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(true);
        return true;
    }
    return false;
}
//
// ParticleFireworks
//

cc::IntrusivePtr<ParticleFireworks> ParticleFireworks::create()
{
    cc::IntrusivePtr ret{new ParticleFireworks()};
    if (!(ret->init()))
    {
        return nullptr;
    }
    return ret;
}

cc::IntrusivePtr<ParticleFireworks> ParticleFireworks::createWithTotalParticles(int numberOfParticles)
{
    cc::IntrusivePtr ret{new ParticleFireworks()};
    if (!(ret->initWithTotalParticles(numberOfParticles)))
    {
        return nullptr;
    }
    return ret;
}

bool ParticleFireworks::initWithTotalParticles(int numberOfParticles)
{
    if (ParticleSystemQuad::initWithTotalParticles(numberOfParticles))
    {
        // duration
        _duration = DURATION_INFINITY;

        // Gravity Mode
        this->_emitterMode = Mode::GRAVITY;

        // Gravity Mode: gravity
        this->modeA.gravity.set(0.0f, -90.0f);

        // Gravity Mode:  radial
        this->modeA.radialAccel    = 0.0f;
        this->modeA.radialAccelVar = 0.0f;

        //  Gravity Mode: speed of particles
        this->modeA.speed    = 180.0f;
        this->modeA.speedVar = 50.0f;

        // emitter position
        Vec2 winSize = _director->getWinSize();
        this->setPosition(winSize.width / 2, winSize.height / 2);

        // angle
        this->_angle    = 90.0f;
        this->_angleVar = 20.0f;

        // life of particles
        this->_life    = 3.5f;
        this->_lifeVar = 1.0f;

        // emits per frame
        this->_emissionRate = _totalParticles / _life;

        // color of particles
        _startColor.r    = 0.5f;
        _startColor.g    = 0.5f;
        _startColor.b    = 0.5f;
        _startColor.a    = 1.0f;
        _startColorVar.r = 0.5f;
        _startColorVar.g = 0.5f;
        _startColorVar.b = 0.5f;
        _startColorVar.a = 0.1f;
        _endColor.r      = 0.1f;
        _endColor.g      = 0.1f;
        _endColor.b      = 0.1f;
        _endColor.a      = 0.2f;
        _endColorVar.r   = 0.1f;
        _endColorVar.g   = 0.1f;
        _endColorVar.b   = 0.1f;
        _endColorVar.a   = 0.2f;

        // size, in pixels
        _startSize    = 8.0f;
        _startSizeVar = 2.0f;
        _endSize      = START_SIZE_EQUAL_TO_END_SIZE;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }
        // additive
        this->setBlendAdditive(false);
        return true;
    }
    return false;
}
//
// ParticleSun
//
cc::IntrusivePtr<ParticleSun> ParticleSun::create()
{
    cc::IntrusivePtr ret{new ParticleSun()};
    if (!(ret->init()))
    {
        return nullptr;
    }
    return ret;
}

cc::IntrusivePtr<ParticleSun> ParticleSun::createWithTotalParticles(int numberOfParticles)
{
    cc::IntrusivePtr ret{new ParticleSun()};
    if (!(ret->initWithTotalParticles(numberOfParticles)))
    {
        return nullptr;
    }
    return ret;
}

bool ParticleSun::initWithTotalParticles(int numberOfParticles)
{
    if (ParticleSystemQuad::initWithTotalParticles(numberOfParticles))
    {
        // additive
        this->setBlendAdditive(true);

        // duration
        _duration = DURATION_INFINITY;

        // Gravity Mode
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Vec2(0, 0));

        // Gravity mode: radial acceleration
        setRadialAccel(0);
        setRadialAccelVar(0);

        // Gravity mode: speed of particles
        setSpeed(20);
        setSpeedVar(5);

        // angle
        _angle    = 90;
        _angleVar = 360;

        // emitter position
        Vec2 winSize = _director->getWinSize();
        this->setPosition(winSize.width / 2, winSize.height / 2);
        setPosVar(Vec2::ZERO);

        // life of particles
        _life    = 1;
        _lifeVar = 0.5f;

        // size, in pixels
        _startSize    = 30.0f;
        _startSizeVar = 10.0f;
        _endSize      = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per seconds
        _emissionRate = _totalParticles / _life;

        // color of particles
        _startColor.r    = 0.76f;
        _startColor.g    = 0.25f;
        _startColor.b    = 0.12f;
        _startColor.a    = 1.0f;
        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.0f;
        _startColorVar.a = 0.0f;
        _endColor.r      = 0.0f;
        _endColor.g      = 0.0f;
        _endColor.b      = 0.0f;
        _endColor.a      = 1.0f;
        _endColorVar.r   = 0.0f;
        _endColorVar.g   = 0.0f;
        _endColorVar.b   = 0.0f;
        _endColorVar.a   = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }

        return true;
    }
    return false;
}

//
// ParticleGalaxy
//

cc::IntrusivePtr<ParticleGalaxy> ParticleGalaxy::create()
{
    cc::IntrusivePtr ret{new ParticleGalaxy()};
    if (!(ret->init()))
    {
        return nullptr;
    }
    return ret;
}

cc::IntrusivePtr<ParticleGalaxy> ParticleGalaxy::createWithTotalParticles(int numberOfParticles)
{
    cc::IntrusivePtr ret{new ParticleGalaxy()};
    if (!(ret->initWithTotalParticles(numberOfParticles)))
    {
        return nullptr;
    }
    return ret;
}

bool ParticleGalaxy::initWithTotalParticles(int numberOfParticles)
{
    if (ParticleSystemQuad::initWithTotalParticles(numberOfParticles))
    {
        // duration
        _duration = DURATION_INFINITY;

        // Gravity Mode
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Vec2(0, 0));

        // Gravity Mode: speed of particles
        setSpeed(60);
        setSpeedVar(10);

        // Gravity Mode: radial
        setRadialAccel(-80);
        setRadialAccelVar(0);

        // Gravity Mode: tangential
        setTangentialAccel(80);
        setTangentialAccelVar(0);

        // angle
        _angle    = 90;
        _angleVar = 360;

        // emitter position
        Vec2 winSize = _director->getWinSize();
        this->setPosition(winSize.width / 2, winSize.height / 2);
        setPosVar(Vec2::ZERO);

        // life of particles
        _life    = 4;
        _lifeVar = 1;

        // size, in pixels
        _startSize    = 37.0f;
        _startSizeVar = 10.0f;
        _endSize      = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = _totalParticles / _life;

        // color of particles
        _startColor.r    = 0.12f;
        _startColor.g    = 0.25f;
        _startColor.b    = 0.76f;
        _startColor.a    = 1.0f;
        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.0f;
        _startColorVar.a = 0.0f;
        _endColor.r      = 0.0f;
        _endColor.g      = 0.0f;
        _endColor.b      = 0.0f;
        _endColor.a      = 1.0f;
        _endColorVar.r   = 0.0f;
        _endColorVar.g   = 0.0f;
        _endColorVar.b   = 0.0f;
        _endColorVar.a   = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(true);
        return true;
    }
    return false;
}

//
// ParticleFlower
//

cc::IntrusivePtr<ParticleFlower> ParticleFlower::create()
{
    cc::IntrusivePtr ret{new ParticleFlower()};
    if (!(ret->init()))
    {
        return nullptr;
    }
    return ret;
}

cc::IntrusivePtr<ParticleFlower> ParticleFlower::createWithTotalParticles(int numberOfParticles)
{
    cc::IntrusivePtr ret{new ParticleFlower()};
    if (!(ret->initWithTotalParticles(numberOfParticles)))
    {
        return nullptr;
    }
    return ret;
}

bool ParticleFlower::initWithTotalParticles(int numberOfParticles)
{
    if (ParticleSystemQuad::initWithTotalParticles(numberOfParticles))
    {
        // duration
        _duration = DURATION_INFINITY;

        // Gravity Mode
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Vec2(0, 0));

        // Gravity Mode: speed of particles
        setSpeed(80);
        setSpeedVar(10);

        // Gravity Mode: radial
        setRadialAccel(-60);
        setRadialAccelVar(0);

        // Gravity Mode: tangential
        setTangentialAccel(15);
        setTangentialAccelVar(0);

        // angle
        _angle    = 90;
        _angleVar = 360;

        // emitter position
        Vec2 winSize = _director->getWinSize();
        this->setPosition(winSize.width / 2, winSize.height / 2);
        setPosVar(Vec2::ZERO);

        // life of particles
        _life    = 4;
        _lifeVar = 1;

        // size, in pixels
        _startSize    = 30.0f;
        _startSizeVar = 10.0f;
        _endSize      = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = _totalParticles / _life;

        // color of particles
        _startColor.r    = 0.50f;
        _startColor.g    = 0.50f;
        _startColor.b    = 0.50f;
        _startColor.a    = 1.0f;
        _startColorVar.r = 0.5f;
        _startColorVar.g = 0.5f;
        _startColorVar.b = 0.5f;
        _startColorVar.a = 0.5f;
        _endColor.r      = 0.0f;
        _endColor.g      = 0.0f;
        _endColor.b      = 0.0f;
        _endColor.a      = 1.0f;
        _endColorVar.r   = 0.0f;
        _endColorVar.g   = 0.0f;
        _endColorVar.b   = 0.0f;
        _endColorVar.a   = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(true);
        return true;
    }
    return false;
}
//
// ParticleMeteor
//

cc::IntrusivePtr<ParticleMeteor> ParticleMeteor::create()
{
    cc::IntrusivePtr ret{new ParticleMeteor()};
    if (!(ret->init()))
    {
        return nullptr;
    }
    return ret;
}

cc::IntrusivePtr<ParticleMeteor> ParticleMeteor::createWithTotalParticles(int numberOfParticles)
{
    cc::IntrusivePtr ret{new ParticleMeteor()};
    if (!(ret->initWithTotalParticles(numberOfParticles)))
    {
        return nullptr;
    }
    return ret;
}

bool ParticleMeteor::initWithTotalParticles(int numberOfParticles)
{
    if (ParticleSystemQuad::initWithTotalParticles(numberOfParticles))
    {
        // duration
        _duration = DURATION_INFINITY;

        // Gravity Mode
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Vec2(-200, 200));

        // Gravity Mode: speed of particles
        setSpeed(15);
        setSpeedVar(5);

        // Gravity Mode: radial
        setRadialAccel(0);
        setRadialAccelVar(0);

        // Gravity Mode: tangential
        setTangentialAccel(0);
        setTangentialAccelVar(0);

        // angle
        _angle    = 90;
        _angleVar = 360;

        // emitter position
        Vec2 winSize = _director->getWinSize();
        this->setPosition(winSize.width / 2, winSize.height / 2);
        setPosVar(Vec2::ZERO);

        // life of particles
        _life    = 2;
        _lifeVar = 1;

        // size, in pixels
        _startSize    = 60.0f;
        _startSizeVar = 10.0f;
        _endSize      = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = _totalParticles / _life;

        // color of particles
        _startColor.r    = 0.2f;
        _startColor.g    = 0.4f;
        _startColor.b    = 0.7f;
        _startColor.a    = 1.0f;
        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.2f;
        _startColorVar.a = 0.1f;
        _endColor.r      = 0.0f;
        _endColor.g      = 0.0f;
        _endColor.b      = 0.0f;
        _endColor.a      = 1.0f;
        _endColorVar.r   = 0.0f;
        _endColorVar.g   = 0.0f;
        _endColorVar.b   = 0.0f;
        _endColorVar.a   = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(true);
        return true;
    }
    return false;
}

//
// ParticleSpiral
//

cc::IntrusivePtr<ParticleSpiral> ParticleSpiral::create()
{
    cc::IntrusivePtr ret{new ParticleSpiral()};
    if (!(ret->init()))
    {
        return nullptr;
    }
    return ret;
}

cc::IntrusivePtr<ParticleSpiral> ParticleSpiral::createWithTotalParticles(int numberOfParticles)
{
    cc::IntrusivePtr ret{new ParticleSpiral()};
    if (!(ret->initWithTotalParticles(numberOfParticles)))
    {
        return nullptr;
    }
    return ret;
}

bool ParticleSpiral::initWithTotalParticles(int numberOfParticles)
{
    if (ParticleSystemQuad::initWithTotalParticles(numberOfParticles))
    {
        // duration
        _duration = DURATION_INFINITY;

        // Gravity Mode
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Vec2(0, 0));

        // Gravity Mode: speed of particles
        setSpeed(150);
        setSpeedVar(0);

        // Gravity Mode: radial
        setRadialAccel(-380);
        setRadialAccelVar(0);

        // Gravity Mode: tangential
        setTangentialAccel(45);
        setTangentialAccelVar(0);

        // angle
        _angle    = 90;
        _angleVar = 0;

        // emitter position
        Vec2 winSize = _director->getWinSize();
        this->setPosition(winSize.width / 2, winSize.height / 2);
        setPosVar(Vec2::ZERO);

        // life of particles
        _life    = 12;
        _lifeVar = 0;

        // size, in pixels
        _startSize    = 20.0f;
        _startSizeVar = 0.0f;
        _endSize      = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = _totalParticles / _life;

        // color of particles
        _startColor.r    = 0.5f;
        _startColor.g    = 0.5f;
        _startColor.b    = 0.5f;
        _startColor.a    = 1.0f;
        _startColorVar.r = 0.5f;
        _startColorVar.g = 0.5f;
        _startColorVar.b = 0.5f;
        _startColorVar.a = 0.0f;
        _endColor.r      = 0.5f;
        _endColor.g      = 0.5f;
        _endColor.b      = 0.5f;
        _endColor.a      = 1.0f;
        _endColorVar.r   = 0.5f;
        _endColorVar.g   = 0.5f;
        _endColorVar.b   = 0.5f;
        _endColorVar.a   = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(false);
        return true;
    }
    return false;
}

//
// ParticleExplosion
//

cc::IntrusivePtr<ParticleExplosion> ParticleExplosion::create()
{
    cc::IntrusivePtr ret{new ParticleExplosion()};
    if (!(ret->init()))
    {
        return nullptr;
    }
    return ret;
}

cc::IntrusivePtr<ParticleExplosion> ParticleExplosion::createWithTotalParticles(int numberOfParticles)
{
    cc::IntrusivePtr ret{new ParticleExplosion()};
    if (!(ret->initWithTotalParticles(numberOfParticles)))
    {
        return nullptr;
    }
    return ret;
}

bool ParticleExplosion::initWithTotalParticles(int numberOfParticles)
{
    if (ParticleSystemQuad::initWithTotalParticles(numberOfParticles))
    {
        // duration
        _duration = 0.1f;

        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Vec2(0, 0));

        // Gravity Mode: speed of particles
        setSpeed(70);
        setSpeedVar(40);

        // Gravity Mode: radial
        setRadialAccel(0);
        setRadialAccelVar(0);

        // Gravity Mode: tangential
        setTangentialAccel(0);
        setTangentialAccelVar(0);

        // angle
        _angle    = 90;
        _angleVar = 360;

        // emitter position
        Vec2 winSize = _director->getWinSize();
        this->setPosition(winSize.width / 2, winSize.height / 2);
        setPosVar(Vec2::ZERO);

        // life of particles
        _life    = 5.0f;
        _lifeVar = 2;

        // size, in pixels
        _startSize    = 15.0f;
        _startSizeVar = 10.0f;
        _endSize      = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = _totalParticles / _duration;

        // color of particles
        _startColor.r    = 0.7f;
        _startColor.g    = 0.1f;
        _startColor.b    = 0.2f;
        _startColor.a    = 1.0f;
        _startColorVar.r = 0.5f;
        _startColorVar.g = 0.5f;
        _startColorVar.b = 0.5f;
        _startColorVar.a = 0.0f;
        _endColor.r      = 0.5f;
        _endColor.g      = 0.5f;
        _endColor.b      = 0.5f;
        _endColor.a      = 0.0f;
        _endColorVar.r   = 0.5f;
        _endColorVar.g   = 0.5f;
        _endColorVar.b   = 0.5f;
        _endColorVar.a   = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(false);
        return true;
    }
    return false;
}

//
// ParticleSmoke
//

cc::IntrusivePtr<ParticleSmoke> ParticleSmoke::create()
{
    cc::IntrusivePtr ret{new ParticleSmoke()};
    if (!(ret->init()))
    {
        return nullptr;
    }
    return ret;
}

cc::IntrusivePtr<ParticleSmoke> ParticleSmoke::createWithTotalParticles(int numberOfParticles)
{
    cc::IntrusivePtr ret{new ParticleSmoke()};
    if (!(ret->initWithTotalParticles(numberOfParticles)))
    {
        return nullptr;
    }
    return ret;
}

bool ParticleSmoke::initWithTotalParticles(int numberOfParticles)
{
    if (ParticleSystemQuad::initWithTotalParticles(numberOfParticles))
    {
        // duration
        _duration = DURATION_INFINITY;

        // Emitter mode: Gravity Mode
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Vec2(0, 0));

        // Gravity Mode: radial acceleration
        setRadialAccel(0);
        setRadialAccelVar(0);

        // Gravity Mode: speed of particles
        setSpeed(25);
        setSpeedVar(10);

        // angle
        _angle    = 90;
        _angleVar = 5;

        // emitter position
        Vec2 winSize = _director->getWinSize();
        this->setPosition(winSize.width / 2, 0);
        setPosVar(Vec2(20, 0));

        // life of particles
        _life    = 4;
        _lifeVar = 1;

        // size, in pixels
        _startSize    = 60.0f;
        _startSizeVar = 10.0f;
        _endSize      = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per frame
        _emissionRate = _totalParticles / _life;

        // color of particles
        _startColor.r    = 0.8f;
        _startColor.g    = 0.8f;
        _startColor.b    = 0.8f;
        _startColor.a    = 1.0f;
        _startColorVar.r = 0.02f;
        _startColorVar.g = 0.02f;
        _startColorVar.b = 0.02f;
        _startColorVar.a = 0.0f;
        _endColor.r      = 0.0f;
        _endColor.g      = 0.0f;
        _endColor.b      = 0.0f;
        _endColor.a      = 1.0f;
        _endColorVar.r   = 0.0f;
        _endColorVar.g   = 0.0f;
        _endColorVar.b   = 0.0f;
        _endColorVar.a   = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(false);
        return true;
    }
    return false;
}

//
// ParticleSnow
//

cc::IntrusivePtr<ParticleSnow> ParticleSnow::create()
{
    cc::IntrusivePtr ret{new ParticleSnow()};
    if (!(ret->init()))
    {
        return nullptr;
    }
    return ret;
}

cc::IntrusivePtr<ParticleSnow> ParticleSnow::createWithTotalParticles(int numberOfParticles)
{
    cc::IntrusivePtr ret{new ParticleSnow()};
    if (!(ret->initWithTotalParticles(numberOfParticles)))
    {
        return nullptr;
    }
    return ret;
}

bool ParticleSnow::initWithTotalParticles(int numberOfParticles)
{
    if (ParticleSystemQuad::initWithTotalParticles(numberOfParticles))
    {
        // duration
        _duration = DURATION_INFINITY;

        // set gravity mode.
        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Vec2(0, -1));

        // Gravity Mode: speed of particles
        setSpeed(5);
        setSpeedVar(1);

        // Gravity Mode: radial
        setRadialAccel(0);
        setRadialAccelVar(1);

        // Gravity mode: tangential
        setTangentialAccel(0);
        setTangentialAccelVar(1);

        // emitter position
        Vec2 winSize = _director->getWinSize();
        this->setPosition(winSize.width / 2, winSize.height + 10);
        setPosVar(Vec2(winSize.width / 2, 0.0f));

        // angle
        _angle    = -90;
        _angleVar = 5;

        // life of particles
        _life    = 45;
        _lifeVar = 15;

        // size, in pixels
        _startSize    = 10.0f;
        _startSizeVar = 5.0f;
        _endSize      = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = 10;

        // color of particles
        _startColor.r    = 1.0f;
        _startColor.g    = 1.0f;
        _startColor.b    = 1.0f;
        _startColor.a    = 1.0f;
        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.0f;
        _startColorVar.a = 0.0f;
        _endColor.r      = 1.0f;
        _endColor.g      = 1.0f;
        _endColor.b      = 1.0f;
        _endColor.a      = 0.0f;
        _endColorVar.r   = 0.0f;
        _endColorVar.g   = 0.0f;
        _endColorVar.b   = 0.0f;
        _endColorVar.a   = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(false);
        return true;
    }
    return false;
}
//
// ParticleRain
//

cc::IntrusivePtr<ParticleRain> ParticleRain::create()
{
    cc::IntrusivePtr ret{new ParticleRain()};
    if (!(ret->init()))
    {
        return nullptr;
    }
    return ret;
}

cc::IntrusivePtr<ParticleRain> ParticleRain::createWithTotalParticles(int numberOfParticles)
{
    cc::IntrusivePtr ret{new ParticleRain()};
    if (!(ret->initWithTotalParticles(numberOfParticles)))
    {
        return nullptr;
    }
    return ret;
}

bool ParticleRain::initWithTotalParticles(int numberOfParticles)
{
    if (ParticleSystemQuad::initWithTotalParticles(numberOfParticles))
    {
        // duration
        _duration = DURATION_INFINITY;

        setEmitterMode(Mode::GRAVITY);

        // Gravity Mode: gravity
        setGravity(Vec2(10, -10));

        // Gravity Mode: radial
        setRadialAccel(0);
        setRadialAccelVar(1);

        // Gravity Mode: tangential
        setTangentialAccel(0);
        setTangentialAccelVar(1);

        // Gravity Mode: speed of particles
        setSpeed(130);
        setSpeedVar(30);

        // angle
        _angle    = -90;
        _angleVar = 5;

        // emitter position
        Vec2 winSize = _director->getWinSize();
        this->setPosition(winSize.width / 2, winSize.height);
        setPosVar(Vec2(winSize.width / 2, 0.0f));

        // life of particles
        _life    = 4.5f;
        _lifeVar = 0;

        // size, in pixels
        _startSize    = 4.0f;
        _startSizeVar = 2.0f;
        _endSize      = START_SIZE_EQUAL_TO_END_SIZE;

        // emits per second
        _emissionRate = 20;

        // color of particles
        _startColor.r    = 0.7f;
        _startColor.g    = 0.8f;
        _startColor.b    = 1.0f;
        _startColor.a    = 1.0f;
        _startColorVar.r = 0.0f;
        _startColorVar.g = 0.0f;
        _startColorVar.b = 0.0f;
        _startColorVar.a = 0.0f;
        _endColor.r      = 0.7f;
        _endColor.g      = 0.8f;
        _endColor.b      = 1.0f;
        _endColor.a      = 0.5f;
        _endColorVar.r   = 0.0f;
        _endColorVar.g   = 0.0f;
        _endColorVar.b   = 0.0f;
        _endColorVar.a   = 0.0f;

        Texture2D* texture = getDefaultTexture();
        if (texture != nullptr)
        {
            setTexture(texture);
        }

        // additive
        this->setBlendAdditive(false);
        return true;
    }
    return false;
}

NS_CC_END
