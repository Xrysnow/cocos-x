#include "AudioFilter.h"
#include "AudioEngine.h"

NS_CC_BEGIN
using namespace AudioInternal;

AudioFilter::AudioFilter()
{
	type = Type::BASIC;
	generateFilter();
}

AudioFilter::AudioFilter(const AudioFilter &s)
	: AudioFilter()
{
	AudioFilter::setParams(s.getParams());
}

AudioFilter::~AudioFilter()
{
	deleteFilter();
}

AudioFilter::Type AudioFilter::getType() const
{
	return type;
}

AudioFilter *AudioFilter::clone()
{
	return new AudioFilter(*this);
}

bool AudioFilter::generateFilter() const
{
#ifdef ALC_EXT_EFX
	if (!AudioEngine::isValid() || !alGenFilters)
		return false;

	const int generation = AudioEngine::getDeviceGeneration();
	if (filterGeneration != generation)
	{
		// The old id belongs to a destroyed context. Never delete it in the
		// new context, where its numeric value may name an unrelated filter.
		filter = AL_FILTER_NULL;
		filterGeneration = generation;
	}
	if (filter != AL_FILTER_NULL)
		return true;

	alGetError();
	alGenFilters(1, &filter);
	if (alGetError() != AL_NO_ERROR)
	{
		filter = AL_FILTER_NULL;
		return false;
	}

	return true;
#else
	return false;
#endif
}

void AudioFilter::deleteFilter() const
{
#ifdef ALC_EXT_EFX
	if (filter != AL_FILTER_NULL && alDeleteFilters
		&& filterGeneration == AudioEngine::getDeviceGeneration())
		alDeleteFilters(1, &filter);
#endif
	filter = AL_FILTER_NULL;
	filterGeneration = -1;
}

ALuint AudioFilter::getFilter() const
{
	if (!AudioEngine::isValid())
		return AL_FILTER_NULL;
	if (filterGeneration != AudioEngine::getDeviceGeneration() || filter == AL_FILTER_NULL)
	{
		if (!generateFilter() || !applyParams())
			return AL_FILTER_NULL;
	}
	return filter;
}

bool AudioFilter::setParams(const ParamMap& params_)
{
	params = params_;
	if (params.find(Parameter::TYPE) == params.end())
		return false;
	type = (Type)(int)params[Parameter::TYPE];

	if (!generateFilter())
		return false;

	return applyParams();
}

bool AudioFilter::applyParams() const
{
#ifdef ALC_EXT_EFX
	if (!alFilteri || !alFilterf)
		return false;
	switch (type)
	{
	case Type::LOWPASS:
		alFilteri(filter, AL_FILTER_TYPE, AL_FILTER_LOWPASS);
		break;
	case Type::HIGHPASS:
		alFilteri(filter, AL_FILTER_TYPE, AL_FILTER_HIGHPASS);
		break;
	case Type::BANDPASS:
		alFilteri(filter, AL_FILTER_TYPE, AL_FILTER_BANDPASS);
		break;
	case Type::BASIC:
	case Type::MAX_ENUM:
		break;
	}

	//failed to make filter specific type - not supported etc.
	if (alGetError() != AL_NO_ERROR)
	{
		deleteFilter();
		return false;
	}

#define clampf(v,l,h) fmax(fmin((v),(h)),(l))
#define PARAMSTR(i,e,v) filter,AL_##e##_##v,clampf(getValue(Parameter::i,AL_##e##_DEFAULT_##v),AL_##e##_MIN_##v,AL_##e##_MAX_##v)
	switch (type)
	{
	case Type::LOWPASS:
		alFilterf(PARAMSTR(VOLUME, LOWPASS, GAIN));
		alFilterf(PARAMSTR(HIGHGAIN, LOWPASS, GAINHF));
		break;
	case Type::HIGHPASS:
		alFilterf(PARAMSTR(VOLUME, HIGHPASS, GAIN));
		alFilterf(PARAMSTR(LOWGAIN, HIGHPASS, GAINLF));
		break;
	case Type::BANDPASS:
		alFilterf(PARAMSTR(VOLUME, BANDPASS, GAIN));
		alFilterf(PARAMSTR(LOWGAIN, BANDPASS, GAINLF));
		alFilterf(PARAMSTR(HIGHGAIN, BANDPASS, GAINHF));
		break;
	case Type::BASIC:
	case Type::MAX_ENUM:
		break;
	}
#undef clampf
#undef PARAMSTR
	//alGetError();

	return true;
#else
	return false;
#endif
}

const AudioFilter::ParamMap& AudioFilter::getParams() const
{
	return params;
}

float AudioFilter::getValue(Parameter in, float def) const
{
	return params.find(in) == params.end() ? def : params.at(in);
}

int AudioFilter::getValue(Parameter in, int def) const
{
	return params.find(in) == params.end() ? def : static_cast<int>(params.at(in));
}

NS_CC_END
