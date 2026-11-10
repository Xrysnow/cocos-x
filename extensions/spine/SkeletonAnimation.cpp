/******************************************************************************
 * Spine Runtimes License Agreement
 * Last updated September 24, 2021. Replaces all prior versions.
 *
 * Copyright (c) 2013-2021, Esoteric Software LLC
 *
 * Integration of the Spine Runtimes into software or otherwise creating
 * derivative works of the Spine Runtimes is permitted under the terms and
 * conditions of Section 2 of the Spine Editor License Agreement:
 * http://esotericsoftware.com/spine-editor-license
 *
 * Otherwise, it is permitted to integrate the Spine Runtimes into software
 * or otherwise create derivative works of the Spine Runtimes (collectively,
 * "Products"), provided that each user of the Products must obtain their own
 * Spine Editor license and redistribution of the Products in any form must
 * include this license and copyright notice.
 *
 * THE SPINE RUNTIMES ARE PROVIDED BY ESOTERIC SOFTWARE LLC "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ESOTERIC SOFTWARE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES,
 * BUSINESS INTERRUPTION, OR LOSS OF USE, DATA, OR PROFITS) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THE SPINE RUNTIMES, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include <algorithm>
#include <spine/Extension.h>
#include <spine/SkeletonAnimation.h>
#include <spine/spine-cocos2dx.h>

USING_NS_CC;
using std::max;
using std::min;
using std::vector;

namespace spine {

	namespace {
		// Keep the active callable alive when a callback replaces or clears its own slot.
		template<typename Listener, typename... Args>
		void invokeListener(Listener listener, Args... args) {
			if (listener) listener(args...);
		}
	}

	typedef struct _TrackEntryListeners {
		StartListener startListener;
		InterruptListener interruptListener;
		EndListener endListener;
		DisposeListener disposeListener;
		CompleteListener completeListener;
		EventListener eventListener;
	} _TrackEntryListeners;

	void animationCallback(AnimationState *state, EventType type, TrackEntry *entry, Event *event) {
		((SkeletonAnimation *) state->getRendererObject())->onAnimationStateEvent(entry, type, event);
	}

	void trackEntryCallback(AnimationState *state, EventType type, TrackEntry *entry, Event *event) {
		((SkeletonAnimation *) state->getRendererObject())->onTrackEntryEvent(entry, type, event);
		if (type == EventType_Dispose) {
			if (entry->getRendererObject()) {
				delete (spine::_TrackEntryListeners *) entry->getRendererObject();
				entry->setRendererObject(NULL);
			}
		}
	}

	static _TrackEntryListeners *getListeners(TrackEntry *entry) {
		if (!entry->getRendererObject()) {
			entry->setRendererObject(new spine::_TrackEntryListeners());
			entry->setListener(trackEntryCallback);
		}
		return (_TrackEntryListeners *) entry->getRendererObject();
	}

	//

	SkeletonAnimation *SkeletonAnimation::createWithData(SkeletonData *skeletonData, bool ownsSkeletonData) {
		SkeletonAnimation *node = new SkeletonAnimation();
		node->initWithData(skeletonData, ownsSkeletonData);
		node->autorelease();
		return node;
	}

	SkeletonAnimation *SkeletonAnimation::createWithJsonFile(const std::string &skeletonJsonFile, Atlas *atlas, float scale) {
		SkeletonAnimation *node = new SkeletonAnimation();
		node->initWithJsonFile(skeletonJsonFile, atlas, scale);
		node->autorelease();
		return node;
	}

	SkeletonAnimation *SkeletonAnimation::createWithJsonFile(const std::string &skeletonJsonFile, const std::string &atlasFile, float scale) {
		SkeletonAnimation *node = new SkeletonAnimation();
		node->initWithJsonFile(skeletonJsonFile, atlasFile, scale);
		node->autorelease();
		return node;
	}

	SkeletonAnimation *SkeletonAnimation::createWithBinaryFile(const std::string &skeletonBinaryFile, Atlas *atlas, float scale) {
		SkeletonAnimation *node = new SkeletonAnimation();
		node->initWithBinaryFile(skeletonBinaryFile, atlas, scale);
		node->autorelease();
		return node;
	}

	SkeletonAnimation *SkeletonAnimation::createWithBinaryFile(const std::string &skeletonBinaryFile, const std::string &atlasFile, float scale) {
		SkeletonAnimation *node = new SkeletonAnimation();
		node->initWithBinaryFile(skeletonBinaryFile, atlasFile, scale);
		node->autorelease();
		return node;
	}


	void SkeletonAnimation::initialize() {
		super::initialize();

		_ownsAnimationStateData = true;
		_updateOnlyIfVisible = false;
		_state = new (__FILE__, __LINE__) AnimationState(new (__FILE__, __LINE__) AnimationStateData(_skeleton->getData()));
		_state->setRendererObject(this);
		_state->setListener(animationCallback);

		_firstDraw = true;
	}

	SkeletonAnimation::SkeletonAnimation()
		: SkeletonRenderer() {
	}

	SkeletonAnimation::~SkeletonAnimation() {
		// Detach callbacks before releasing state. Never retain a node during destruction.
		_state->setListener(static_cast<AnimationStateListenerObject *>(nullptr));
		_state->setRendererObject(nullptr);
		_startListener = nullptr;
		_interruptListener = nullptr;
		_endListener = nullptr;
		_disposeListener = nullptr;
		_completeListener = nullptr;
		_eventListener = nullptr;
		_preUpdateListener = nullptr;
		_postUpdateListener = nullptr;

		if (_ownsAnimationStateData) delete _state->getData();
		delete _state;
	}

	void SkeletonAnimation::update(float deltaTime) {
		if (_updateOnlyIfVisible && !isVisible()) return;

		// Callbacks may remove the last external owner; retain through all native work.
		const RefPtr<SkeletonAnimation> keepAlive(this);
		super::update(deltaTime);

		deltaTime *= _timeScale;
		invokeListener(_preUpdateListener, this);
		_state->update(deltaTime);
		_state->apply(*_skeleton);
		_skeleton->updateWorldTransform();
		invokeListener(_postUpdateListener, this);
	}

	void SkeletonAnimation::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4 &parentTransform, uint32_t parentFlags) {
		// Node::visit continues using this node after draw's initial update(0) callbacks.
		const RefPtr<SkeletonAnimation> keepAlive(this);
		super::visit(renderer, parentTransform, parentFlags);
	}

	void SkeletonAnimation::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t transformFlags) {
		const RefPtr<SkeletonAnimation> keepAlive(this);
		if (_firstDraw) {
			_firstDraw = false;
			update(0);
		}
		super::draw(renderer, transform, transformFlags);
	}

	void SkeletonAnimation::setAnimationStateData(AnimationStateData *stateData) {
		CCASSERT(stateData, "stateData cannot be null.");

		if (_ownsAnimationStateData) delete _state->getData();
		delete _state;

		_ownsAnimationStateData = false;
		_state = new (__FILE__, __LINE__) AnimationState(stateData);
		_state->setRendererObject(this);
		_state->setListener(animationCallback);
	}

	void SkeletonAnimation::setMix(const std::string &fromAnimation, const std::string &toAnimation, float duration) {
		_state->getData()->setMix(fromAnimation.c_str(), toAnimation.c_str(), duration);
	}

	TrackEntry *SkeletonAnimation::setAnimation(int trackIndex, const std::string &name, bool loop) {
		const RefPtr<SkeletonAnimation> keepAlive(this);
		Animation *animation = _skeleton->getData()->findAnimation(name.c_str());
		if (!animation) {
			log("Spine: Animation not found: %s", name.c_str());
			return 0;
		}
		return _state->setAnimation(trackIndex, animation, loop);
	}

	TrackEntry *SkeletonAnimation::addAnimation(int trackIndex, const std::string &name, bool loop, float delay) {
		const RefPtr<SkeletonAnimation> keepAlive(this);
		Animation *animation = _skeleton->getData()->findAnimation(name.c_str());
		if (!animation) {
			log("Spine: Animation not found: %s", name.c_str());
			return 0;
		}
		return _state->addAnimation(trackIndex, animation, loop, delay);
	}

	TrackEntry *SkeletonAnimation::setEmptyAnimation(int trackIndex, float mixDuration) {
		const RefPtr<SkeletonAnimation> keepAlive(this);
		return _state->setEmptyAnimation(trackIndex, mixDuration);
	}

	void SkeletonAnimation::setEmptyAnimations(float mixDuration) {
		const RefPtr<SkeletonAnimation> keepAlive(this);
		_state->setEmptyAnimations(mixDuration);
	}

	TrackEntry *SkeletonAnimation::addEmptyAnimation(int trackIndex, float mixDuration, float delay) {
		const RefPtr<SkeletonAnimation> keepAlive(this);
		return _state->addEmptyAnimation(trackIndex, mixDuration, delay);
	}

	Animation *SkeletonAnimation::findAnimation(const std::string &name) const {
		return _skeleton->getData()->findAnimation(name.c_str());
	}

	TrackEntry *SkeletonAnimation::getCurrent(int trackIndex) {
		return _state->getCurrent(trackIndex);
	}

	void SkeletonAnimation::clearTracks() {
		const RefPtr<SkeletonAnimation> keepAlive(this);
		_state->clearTracks();
	}

	void SkeletonAnimation::clearTrack(int trackIndex) {
		const RefPtr<SkeletonAnimation> keepAlive(this);
		_state->clearTrack(trackIndex);
	}

	void SkeletonAnimation::onAnimationStateEvent(TrackEntry *entry, EventType type, Event *event) {
		switch (type) {
			case EventType_Start:
				invokeListener(_startListener, entry);
				break;
			case EventType_Interrupt:
				invokeListener(_interruptListener, entry);
				break;
			case EventType_End:
				invokeListener(_endListener, entry);
				break;
			case EventType_Dispose:
				invokeListener(_disposeListener, entry);
				break;
			case EventType_Complete:
				invokeListener(_completeListener, entry);
				break;
			case EventType_Event:
				invokeListener(_eventListener, entry, event);
				break;
		}
	}

	void SkeletonAnimation::onTrackEntryEvent(TrackEntry *entry, EventType type, Event *event) {
		if (!entry->getRendererObject()) return;
		_TrackEntryListeners *listeners = (_TrackEntryListeners *) entry->getRendererObject();
		switch (type) {
			case EventType_Start:
				invokeListener(listeners->startListener, entry);
				break;
			case EventType_Interrupt:
				invokeListener(listeners->interruptListener, entry);
				break;
			case EventType_End:
				invokeListener(listeners->endListener, entry);
				break;
			case EventType_Dispose:
				invokeListener(listeners->disposeListener, entry);
				break;
			case EventType_Complete:
				invokeListener(listeners->completeListener, entry);
				break;
			case EventType_Event:
				invokeListener(listeners->eventListener, entry, event);
				break;
		}
	}

	void SkeletonAnimation::setStartListener(const StartListener &listener) {
		_startListener = listener;
	}

	void SkeletonAnimation::setInterruptListener(const InterruptListener &listener) {
		_interruptListener = listener;
	}

	void SkeletonAnimation::setEndListener(const EndListener &listener) {
		_endListener = listener;
	}

	void SkeletonAnimation::setDisposeListener(const DisposeListener &listener) {
		_disposeListener = listener;
	}

	void SkeletonAnimation::setCompleteListener(const CompleteListener &listener) {
		_completeListener = listener;
	}

	void SkeletonAnimation::setEventListener(const EventListener &listener) {
		_eventListener = listener;
	}

	void SkeletonAnimation::setPreUpdateWorldTransformsListener(const UpdateWorldTransformsListener &listener) {
		_preUpdateListener = listener;
	}

	void SkeletonAnimation::setPostUpdateWorldTransformsListener(const UpdateWorldTransformsListener &listener) {
		_postUpdateListener = listener;
	}

	void SkeletonAnimation::setTrackStartListener(TrackEntry *entry, const StartListener &listener) {
		getListeners(entry)->startListener = listener;
	}

	void SkeletonAnimation::setTrackInterruptListener(TrackEntry *entry, const InterruptListener &listener) {
		getListeners(entry)->interruptListener = listener;
	}

	void SkeletonAnimation::setTrackEndListener(TrackEntry *entry, const EndListener &listener) {
		getListeners(entry)->endListener = listener;
	}

	void SkeletonAnimation::setTrackDisposeListener(TrackEntry *entry, const DisposeListener &listener) {
		getListeners(entry)->disposeListener = listener;
	}

	void SkeletonAnimation::setTrackCompleteListener(TrackEntry *entry, const CompleteListener &listener) {
		getListeners(entry)->completeListener = listener;
	}

	void SkeletonAnimation::setTrackEventListener(TrackEntry *entry, const EventListener &listener) {
		getListeners(entry)->eventListener = listener;
	}

	AnimationState *SkeletonAnimation::getState() const {
		return _state;
	}

	void SkeletonAnimation::setUpdateOnlyIfVisible(bool status) {
		_updateOnlyIfVisible = status;
	}

}// namespace spine
