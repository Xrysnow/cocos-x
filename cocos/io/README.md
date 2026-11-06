# cocos-x byte streams

The io module supplies synchronous byte streams to cocos2d consumers. Include
the headers explicitly and link the existing cocos2d target. Network transports
and FFmpeg AVIO integration are separate future consumers.

## Ownership and locking

Stream and MemoryBuffer derive from Ref. Their constructors require the Atomic
policy; factories return Result<ThreadSafeRefPtr<T>> and never autorelease.
Each participating constructor forwards RefConstructionToken. Keep an owning
pointer while using a borrowed raw pointer.

Distinct strong-pointer instances can cross threads. The same pointer variable
and stream state still require synchronization. A stream has one cursor; copying
its strong pointer does not create an independent reader. MemoryStream::fromBuffer
creates independent cursors over immutable data; reopening a file creates an
independent file handle.

Use StreamLock around a complete shared read/seek sequence. Individual methods,
including readExact/writeAll, do not acquire the non-recursive lock themselves.
The guard retains its stream until after unlocking. AudioStreamAdapter forwards
its lock to the source; do not externally lock an input while calling a decoder
that acquires that same lock.

BufferedStream owns access to its source cursor and closes it on close/destruction.
Do not bypass the wrapper while it is in use. Lua-bound wrapper objects remain
confined to the scripting thread; core stream ownership alone does not make Lua
or autorelease pools thread-safe. File factories require normal FileUtils/platform
initialization and obey the host's path/delegate synchronization rules.

## Results and positions

- Result<T> and Status convert to true on success. StreamError converts to true
  when an error is present. ErrorCode, nativeCode and domain carry diagnostics.
- IoResult reports transferred bytes and IoStatus. Preserve transferred bytes
  even when followed by EOF, cancellation, waiting or an error.
- Ok permits short operations, but must make positive progress for nonzero
  requests. EndOfStream means a request could not be satisfied at the input end.
- readExact/writeAll accumulate short operations and stop on zero progress or a
  non-Ok result. copyTo reports consumed source bytes separately from accepted
  destination bytes; it rejects aliases sharing cursorIdentity().
- readAll(maxBytes) never consumes an extra byte to test EOF. At the exact limit,
  unknown length yields LimitExceeded, with already read data retained in value.
  WouldBlock/Cancelled/Timeout map to corresponding ErrorCode values in Result.
- Positions and lengths are nonnegative int64_t values. Transfer lengths use
  size_t. size() returns Result<optional<int64_t>>; an empty optional is unknown
  length, while an engaged zero is an empty stream.
- Seeking exactly to EOF is valid. Writable growable streams can seek beyond EOF;
  writes/resize perform growth and zero-fill holes. Read-only/fixed streams reject
  out-of-range seeks. Invalid arguments leave the cursor unchanged.
- Resize clamps the cursor to a shortened length. Unexpected backend position
  changes and malformed transfer results are reported rather than silently used.
- Closed or unsupported operations fail explicitly. Flush submits user-space
  buffered bytes; sync additionally requests backend durability.

These APIs use C++17. Nonseekable input can report a logical consumed-byte cursor
and unknown length. Consumers must check the capabilities they need.

## Memory

MemoryStream::create creates zero-filled, growable memory with an optional
maximum capacity. copy copies input; move transfers a vector. reserve changes
capacity without changing length.

freeze permanently disables writes and exposes the MemoryBuffer for independent
read-only streams. Only const data views are public. Growth and close invalidate
borrowed views. No reference-count snapshot is used to infer exclusive ownership.

borrow and borrowWritable create fixed-size views. An optional Atomic Ref owner
extends storage lifetime; external mutation aliases and owner lifetime are still
the caller's responsibility. Fixed writes report partial progress and NoSpace.
Overlapping memory transfers and input aliases across growth are handled.

```cpp
#include "io/MemoryStream.h"

auto writable = cocos2d::io::MemoryStream::create(0, 1024 * 1024);
if (!writable)
    return;
auto written = writable.value->writeAll("example", 7);
if (!written)
    return;
auto immutable = writable.value->freeze();
if (!immutable)
    return;
auto reader = cocos2d::io::MemoryStream::fromBuffer(immutable.value);
// reader owns the data and starts at zero, independently of writable's cursor.
```

## Files and buffering

io::FileStream wraps the existing cocos2d::FileStream backend through
FileUtils::openFileStream. FileOpenOptions separates access, creation policy and
append. Read inputs follow FileUtils search paths; write destinations are explicit.
Android assets/OBB are read-only, and OBB retains its backend offset limit.

Legacy Mode values and the virtual openFileStream hook remain available.
Explicit options are encoded into Mode for that hook; custom backends can use
decodeOpenOptions and declare isReadable/isWritable/canResize/canSync. New
optional backend mutations default to unsupported. Consumers must rebuild after
the FileStream virtual interface extension.

The raw io::FileStream has no user-space cache. Compose BufferedStream to select
read/write capacities, defaulting to 64 KiB per enabled direction and allocated
lazily. Zero disables a direction's cache, not the OS cache. Append always writes
through; its configured writeCapacity does not allocate an append write cache.

```cpp
#include "io/FileStream.h"
#include "io/BufferedStream.h"

auto file = cocos2d::io::FileStream::open("asset.bin");
if (!file)
    return;
auto input = cocos2d::io::BufferedStream::create(file.value, {256 * 1024, 0});
if (!input)
    return;
auto contents = input.value->readAll(8 * 1024 * 1024);
if (!contents)
    return;
auto closed = input.value->close();
```

tell and size account for accepted writes and unread prefetch. Seek/read/write
switches reconcile the real backend cursor. Large operations can bypass empty
caches. setBufferOptions requires the same external lock as I/O and preserves
pending data on failure. Nonseekable read-only input is supported; shrinking
below unread prefetched bytes is rejected. Nonseekable duplex input is not
supported by this single-cursor wrapper.

A partially failed flush retains the unwritten tail. A close failing during flush
leaves the stream open for retry. After the backend close is attempted, its handle
is consumed and never closed a second time; repeated close returns the recorded
result. Destruction releases resources but cannot report a successful write-back:
callers requiring that guarantee must explicitly check close.

## Audio adapter

AudioStreamAdapter::create accepts a readable, seekable stream with known length
and returns an owning Atomic adapter. It preserves the legacy bool-read contract
and exposes the last IoResult for diagnostics. It does not change existing
autoreleased AudioStream factories or their FileOpener behavior.

```cpp
#include "audio/AudioStreamAdapter.h"
#include "audio/AudioDecoder.h"

// input is a live StreamPtr or ThreadSafeRefPtr<BufferedStream>.
auto audio = cocos2d::AudioStreamAdapter::create(input);
if (!audio)
    return;
// The legacy decoder factory still needs the usual autorelease pool.
auto decoder = cocos2d::AudioDecoder::createFromStream(
    audio.value.get(), 16384, cocos2d::AudioDecoder::DecoderType::WAV);
```

Generic network input does not imply that current decoders accept unknown length
or nonseekable streams. Decoder and LuaSTG resource API migration is separate.
