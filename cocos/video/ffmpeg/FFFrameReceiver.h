#pragma once
#include "base/CCRef.h"
#include "video/VideoCommon.h"
#include "video/FFInfo.h"

namespace ffmpeg
{
	class FrameReceiver : public cocos2d::Ref
	{
	public:
		virtual ~FrameReceiver() = default;
		// Provide storage for the next received frame. Null indicates allocation failure.
		virtual AVFrame* alloc() = 0;
		virtual void receive(AVFrame* frame, MetaData* metaData) = 0;
		// called at EOF
		virtual void end() = 0;
		// clear internal buffer
		virtual void clear() = 0;
		/**
		 * Return whether we have all information we need to start receiving data.
		 * A container might only be primed once it received at least one frame from each source
		 * it will be muxing together.
		 */
		virtual bool prepare() = 0;
		virtual AVMediaType getMediaType() = 0;
	};
}
