#include "AudioDirectRenderer.h"
#include <algorithm>
#include <cstring>

namespace cc::audio::detail {

DirectRenderer::DirectRenderer(const AudioDirectInput& input, unsigned outputRate, const std::atomic<bool>& looping,
    std::stop_token cancellation)
    : _input(input), _outputRate(outputRate), _looping(looping), _cancellation(std::move(cancellation)),
      _frameBytes(input.channels * (input.bitDepth / 8))
{
}

bool DirectRenderer::start(std::uint64_t frame)
{
    if (!_input.pcm)
    {
        _decoder = _input.openDecoder(_cancellation);
        if (!_decoder || _decoder->getSampleRate() != _input.sampleRate ||
            _decoder->getChannelCount() != _input.channels || _decoder->getBitDepth() != _input.bitDepth ||
            (frame != 0 && !_decoder->seek(static_cast<std::int64_t>(frame))))
            return false;
    }
    _position = _readPosition = frame;
    _current = read(_sample);
    if (_current)
        _next = readNext();
    return !_failed;
}

bool DirectRenderer::read(Samples& samples)
{
    if (_input.totalFrames && _readPosition >= *_input.totalFrames)
        return false;

    const std::uint8_t* bytes = nullptr;
    if (_input.pcm)
    {
        if (_readPosition >= _input.pcm->size() / _frameBytes)
            return false;
        bytes = _input.pcm->data() + _readPosition * _frameBytes;
    }
    else
    {
        if (_offset == _bufferSize)
        {
            auto request = _buffer.size() - _buffer.size() % _frameBytes;
            if (_input.totalFrames)
                request = std::min<std::uint64_t>(request / _frameBytes, *_input.totalFrames - _readPosition) * _frameBytes;
            const auto read = _decoder->decode(reinterpret_cast<char*>(_buffer.data()), request);
            if (read <= 0 || read % _frameBytes != 0 || static_cast<std::uint64_t>(read) > request || _decoder->hasIoError())
            {
                _failed = read < 0 || read > 0 || _decoder->hasIoError() ||
                    (_input.totalFrames && _readPosition < *_input.totalFrames);
                return false;
            }
            _offset = 0;
            _bufferSize = static_cast<size_t>(read);
        }
        bytes = _buffer.data() + _offset;
        _offset += _frameBytes;
    }
    for (int channel = 0; channel < _input.channels; ++channel)
    {
        if (_input.bitDepth == 8)
            samples[channel] = (static_cast<int>(bytes[channel]) - 128) * 256.0f;
        else
        {
            std::int16_t value;
            std::memcpy(&value, bytes + channel * sizeof(value), sizeof(value));
            samples[channel] = value;
        }
    }
    ++_readPosition;
    return true;
}

bool DirectRenderer::readNext()
{
    _nextPosition = _readPosition;
    if (read(_nextSample))
        return true;
    if (!_looping || _readPosition == 0 || _failed)
        return false;

    if (_decoder && !_decoder->seek(0))
    {
        _failed = true;
        return false;
    }
    _offset = _bufferSize = 0;
    _nextPosition = _readPosition = 0;
    return read(_nextSample);
}

bool DirectRenderer::fill(DirectBlock& block)
{
    block.count = 0;
    while (_current && !_failed && block.count < block.frames.size())
    {
        if (!_next && _looping)
            _next = readNext();

        auto& frame = block.frames[block.count++];
        frame.sample = _sample;
        if (_next && _phase)
        {
            const auto fraction = static_cast<float>(_phase) / _outputRate;
            for (int channel = 0; channel < _input.channels; ++channel)
                frame.sample[channel] += (_nextSample[channel] - _sample[channel]) * fraction;
        }

        _phase += _input.sampleRate;
        while (_phase >= _outputRate && _current)
        {
            _phase -= _outputRate;
            _current = _next;
            if (_current)
            {
                _position = _nextPosition;
                _sample = _nextSample;
                _next = readNext();
            }
            else
            {
                ++_position;
                _phase = 0;
            }
        }
        frame.position = (_position + static_cast<double>(_phase) / _outputRate) / _input.sampleRate;
    }
    return !_failed;
}

} // namespace cc::audio::detail
