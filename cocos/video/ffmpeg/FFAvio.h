#pragma once
#include "io/Stream.h"
#include <atomic>
#include <memory>

struct AVIOContext;

namespace ffmpeg
{
	class AvioInput final
	{
	public:
		static std::unique_ptr<AvioInput> create(cocos2d::io::StreamPtr source,
			const std::atomic<bool>* stop);
		~AvioInput();

		AVIOContext* get() const { return context; }
		int readError() const;
		bool isCancelled() const;

	private:
		AvioInput(cocos2d::io::StreamPtr source, const std::atomic<bool>* stop);
		AvioInput(const AvioInput&) = delete;
		AvioInput& operator=(const AvioInput&) = delete;
		static int read(void* opaque, uint8_t* buffer, int length) noexcept;
		static int64_t seek(void* opaque, int64_t offset, int whence) noexcept;

		cocos2d::io::StreamPtr source;
		const std::atomic<bool>* stop;
		AVIOContext* context = nullptr;
		int terminalRead = 0;
	};
}
