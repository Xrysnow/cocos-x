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
		static std::unique_ptr<AvioInput> create(cc::io::StreamPtr source,
			const std::atomic<bool>* stop);
		~AvioInput();

		AVIOContext* get() const { return context; }
		int readError() const;
		bool isCancelled() const;

	private:
		AvioInput(cc::io::StreamPtr source, const std::atomic<bool>* stop);
		AvioInput(const AvioInput&) = delete;
		AvioInput& operator=(const AvioInput&) = delete;
		static int read(void* opaque, uint8_t* buffer, int length) noexcept;
		static int64_t seek(void* opaque, int64_t offset, int whence) noexcept;

		cc::io::StreamPtr source;
		const std::atomic<bool>* stop;
		AVIOContext* context = nullptr;
		int terminalRead = 0;
	};
}
