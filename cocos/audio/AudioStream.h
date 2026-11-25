#pragma once
#include "base/Ref.h"
#include <cstdint>
#include <functional>
#include <string>

NS_CC_BEGIN

class CC_DLL AudioStream : public Ref
{
public:
	enum class SeekOrigin
	{
		BEGINNING = 0,
		CURRENT = 1,
		END = 2
	};

	virtual uint64_t size() = 0;
	virtual uint64_t tell() = 0;
	virtual bool seek(SeekOrigin origin, int64_t offset) = 0;
	virtual bool read(uint8_t* dst, uint64_t length, uint64_t* bytesRead = nullptr) = 0;

	// Callers lock a complete sequence of cursor operations. Individual operations
	// do not acquire this non-recursive lock; a shared stream has one cursor.
	virtual void lock() = 0;
	virtual void unlock() = 0;
	virtual ~AudioStream() = default;

	using FileOpener = std::function<cc::IntrusivePtr<AudioStream>(const std::string&)>;
	// The factory owns its snapshot and creates a fresh reader at offset zero.
	// Playback workers may call it concurrently. Opening and individual reads must
	// be finite, and the factory must not require host services.
	using ReopenFactory = std::function<cc::IntrusivePtr<AudioStream>()>;
	virtual ReopenFactory getReopenFactory() const { return {}; }
	virtual bool hasIoError() const noexcept { return false; }

	// Configure only during host initialization/final shutdown, with no concurrent
	// stream creation. The callback runs synchronously on the creating thread and
	// returns an owning IntrusivePtr. A null result does not fall back to files.
	// For explicit fallback call createFromLocalFile(), never createFromFile().
	// AudioEngine::end() does not reset this host configuration.
	static void setFileOpener(FileOpener opener);
	static cc::IntrusivePtr<AudioStream> createFromFile(const std::string& path);

	// Reads from a platform source directly, bypassing the audio callback and ZIP mounts.
	// Uses a new file handle/cursor; the returned pointer owns the stream.
	static cc::IntrusivePtr<AudioStream> createFromLocalFile(const std::string& path);
protected:
	AudioStream() = default;
	explicit AudioStream(RefConstructionToken token) : Ref(token) {}
};

NS_CC_END
