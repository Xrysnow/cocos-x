#pragma once
#include "base/CCRef.h"
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

	using FileOpener = std::function<AudioStream*(const std::string&)>;

	// Configure only during host initialization/final shutdown, with no concurrent
	// stream creation. The callback runs synchronously on the creating thread and
	// returns an autoreleased stream. A null result does not fall back to files.
	// For explicit fallback call createFromLocalFile(), never createFromFile().
	// AudioEngine::end() does not reset this host configuration.
	static void setFileOpener(FileOpener opener);
	static AudioStream* createFromFile(const std::string& path);

	// Bypasses the audio callback, while retaining FileUtils path/delegate behavior.
	// Uses a new file handle/cursor and requires the usual cocos autorelease pool.
	static AudioStream* createFromLocalFile(const std::string& path);
};

NS_CC_END
