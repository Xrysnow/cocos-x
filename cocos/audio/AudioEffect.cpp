#include "AudioEffect.h"
#include "AudioEngine.h"
#include <cmath>
#ifdef ECHO
#undef ECHO
#endif

NS_CC_BEGIN
using namespace AudioInternal;

AudioEffect::AudioEffect()
{
	generateEffect();
}

AudioEffect::AudioEffect(const AudioEffect &s)
	: AudioEffect()
{
	AudioEffect::setParams(s.getParams());
}

AudioEffect::~AudioEffect()
{
	deleteEffect();
}

AudioEffect *AudioEffect::clone()
{
	return new AudioEffect(*this);
}

bool AudioEffect::generateEffect()
{
#ifdef ALC_EXT_EFX
	if (!alGenEffects)
		return false;

	if (effect != AL_EFFECT_NULL)
		return true;

	alGenEffects(1, &effect);
	return alGetError() == AL_NO_ERROR;
#else
	return false;
#endif
}

void AudioEffect::deleteEffect()
{
#ifdef ALC_EXT_EFX
	if (effect != AL_EFFECT_NULL)
		alDeleteEffects(1, &effect);
#endif
	effect = AL_EFFECT_NULL;
}

ALuint AudioEffect::getEffect() const
{
	return effect;
}

bool AudioEffect::setParams(const ParamMap& params_)
{
	params = params_;
	// parameter table without EFFECT_TYPE entry is illegal
	if (params.find(Parameter::TYPE) == params.end())
		return false;
	type = (Type)(int)params[Parameter::TYPE];

	if (!generateEffect())
		return false;

#ifdef ALC_EXT_EFX
	switch (type)
	{
	case Type::REVERB:
		alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_REVERB);
		break;
	case Type::CHORUS:
		alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_CHORUS);
		break;
	case Type::DISTORTION:
		alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_DISTORTION);
		break;
	case Type::ECHO:
		alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_ECHO);
		break;
	case Type::FLANGER:
		alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_FLANGER);
		break;
	case Type::FREQSHIFTER:
		alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_FREQUENCY_SHIFTER);
		break;
	case Type::MORPHER:
		alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_VOCAL_MORPHER);
		break;
	case Type::PITCHSHIFTER:
		alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_PITCH_SHIFTER);
		break;
	case Type::MODULATOR:
		alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_RING_MODULATOR);
		break;
	case Type::AUTOWAH:
		alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_AUTOWAH);
		break;
	case Type::COMPRESSOR:
		alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_COMPRESSOR);
		break;
	case Type::EQUALIZER:
		alEffecti(effect, AL_EFFECT_TYPE, AL_EFFECT_EQUALIZER);
		break;
	case Type::BASIC:
	case Type::MAX_ENUM:
		break;
	}

	// failed to make effect specific type - not supported etc.
	if (alGetError() != AL_NO_ERROR)
	{
		deleteEffect();
		return false;
	}

#define clampf(v,l,h) fmax(fmin((v),(h)),(l))
#define PARAMSTR(i,e,v) effect,AL_##e##_##v,clampf(getValue(Parameter::i,AL_##e##_DEFAULT_##v),AL_##e##_MIN_##v,AL_##e##_MAX_##v)
	switch (type)
	{
	case Type::REVERB:
	{
		alEffectf(PARAMSTR(REVERB_GAIN, REVERB, GAIN));
		alEffectf(PARAMSTR(REVERB_HFGAIN, REVERB, GAINHF));
		alEffectf(PARAMSTR(REVERB_DENSITY, REVERB, DENSITY));
		alEffectf(PARAMSTR(REVERB_DIFFUSION, REVERB, DIFFUSION));
		alEffectf(PARAMSTR(REVERB_DECAY, REVERB, DECAY_TIME));
		alEffectf(PARAMSTR(REVERB_HFDECAY, REVERB, DECAY_HFRATIO));
		alEffectf(PARAMSTR(REVERB_EARLYGAIN, REVERB, REFLECTIONS_GAIN));
		alEffectf(PARAMSTR(REVERB_EARLYDELAY, REVERB, REFLECTIONS_DELAY));
		alEffectf(PARAMSTR(REVERB_LATEGAIN, REVERB, LATE_REVERB_GAIN));
		alEffectf(PARAMSTR(REVERB_LATEDELAY, REVERB, LATE_REVERB_DELAY));;
		alEffectf(PARAMSTR(REVERB_ROLLOFF, REVERB, ROOM_ROLLOFF_FACTOR));
		alEffectf(PARAMSTR(REVERB_AIRHFGAIN, REVERB, AIR_ABSORPTION_GAINHF));
		alEffecti(effect, AL_REVERB_DECAY_HFLIMIT, getValue(Parameter::REVERB_HFLIMITER, AL_REVERB_DEFAULT_DECAY_HFLIMIT));
		break;
	}
	case Type::CHORUS:
	{
		Waveform wave = static_cast<Waveform>(getValue(Parameter::CHORUS_WAVEFORM, static_cast<int>(Waveform::MAX_ENUM)));
		if (wave == Waveform::SINE)
			alEffecti(effect, AL_CHORUS_WAVEFORM, AL_CHORUS_WAVEFORM_SINUSOID);
		else if (wave == Waveform::TRIANGLE)
			alEffecti(effect, AL_CHORUS_WAVEFORM, AL_CHORUS_WAVEFORM_TRIANGLE);
		else
			alEffecti(effect, AL_CHORUS_WAVEFORM, AL_CHORUS_DEFAULT_WAVEFORM);

		alEffecti(PARAMSTR(CHORUS_PHASE, CHORUS, PHASE));
		alEffectf(PARAMSTR(CHORUS_RATE, CHORUS, RATE));
		alEffectf(PARAMSTR(CHORUS_DEPTH, CHORUS, DEPTH));
		alEffectf(PARAMSTR(CHORUS_FEEDBACK, CHORUS, FEEDBACK));
		alEffectf(PARAMSTR(CHORUS_DELAY, CHORUS, DELAY));
		break;
	}
	case Type::DISTORTION:
		alEffectf(PARAMSTR(DISTORTION_GAIN, DISTORTION, GAIN));
		alEffectf(PARAMSTR(DISTORTION_EDGE, DISTORTION, EDGE));
		alEffectf(PARAMSTR(DISTORTION_LOWCUT, DISTORTION, LOWPASS_CUTOFF));
		alEffectf(PARAMSTR(DISTORTION_EQCENTER, DISTORTION, EQCENTER));
		alEffectf(PARAMSTR(DISTORTION_EQBAND, DISTORTION, EQBANDWIDTH));
		break;

	case Type::ECHO:
		alEffectf(PARAMSTR(ECHO_DELAY, ECHO, DELAY));
		alEffectf(PARAMSTR(ECHO_LRDELAY, ECHO, LRDELAY));
		alEffectf(PARAMSTR(ECHO_DAMPING, ECHO, DAMPING));
		alEffectf(PARAMSTR(ECHO_FEEDBACK, ECHO, FEEDBACK));
		alEffectf(PARAMSTR(ECHO_SPREAD, ECHO, SPREAD));
		break;

	case Type::FLANGER:
	{
		Waveform wave = static_cast<Waveform>(getValue(Parameter::FLANGER_WAVEFORM, static_cast<int>(Waveform::MAX_ENUM)));
		if (wave == Waveform::SINE)
			alEffecti(effect, AL_FLANGER_WAVEFORM, AL_FLANGER_WAVEFORM_SINUSOID);
		else if (wave == Waveform::TRIANGLE)
			alEffecti(effect, AL_FLANGER_WAVEFORM, AL_FLANGER_WAVEFORM_TRIANGLE);
		else
			alEffecti(effect, AL_FLANGER_WAVEFORM, AL_FLANGER_DEFAULT_WAVEFORM);

		alEffecti(PARAMSTR(FLANGER_PHASE, FLANGER, PHASE));
		alEffectf(PARAMSTR(FLANGER_RATE, FLANGER, RATE));
		alEffectf(PARAMSTR(FLANGER_DEPTH, FLANGER, DEPTH));
		alEffectf(PARAMSTR(FLANGER_FEEDBACK, FLANGER, FEEDBACK));
		alEffectf(PARAMSTR(FLANGER_DELAY, FLANGER, DELAY));
		break;
	}
	case Type::FREQSHIFTER:
	{
		alEffectf(PARAMSTR(FREQSHIFTER_FREQ,FREQUENCY_SHIFTER,FREQUENCY));

		Direction dir = static_cast<Direction>(getValue(Parameter::FREQSHIFTER_LEFTDIR, static_cast<int>(Direction::MAX_ENUM)));
		if (dir == Direction::NONE)
			alEffecti(effect, AL_FREQUENCY_SHIFTER_LEFT_DIRECTION, AL_FREQUENCY_SHIFTER_DIRECTION_OFF);
		else if(dir == Direction::UP)
			alEffecti(effect, AL_FREQUENCY_SHIFTER_LEFT_DIRECTION, AL_FREQUENCY_SHIFTER_DIRECTION_UP);
		else if(dir == Direction::DOWN)
			alEffecti(effect, AL_FREQUENCY_SHIFTER_LEFT_DIRECTION, AL_FREQUENCY_SHIFTER_DIRECTION_DOWN);
		else
			alEffecti(effect, AL_FREQUENCY_SHIFTER_LEFT_DIRECTION, AL_FREQUENCY_SHIFTER_DEFAULT_LEFT_DIRECTION);

		dir = static_cast<Direction>(getValue(Parameter::FREQSHIFTER_RIGHTDIR, static_cast<int>(Direction::MAX_ENUM)));
		if (dir == Direction::NONE)
			alEffecti(effect, AL_FREQUENCY_SHIFTER_RIGHT_DIRECTION, AL_FREQUENCY_SHIFTER_DIRECTION_OFF);
		else if(dir == Direction::UP)
			alEffecti(effect, AL_FREQUENCY_SHIFTER_RIGHT_DIRECTION, AL_FREQUENCY_SHIFTER_DIRECTION_UP);
		else if(dir == Direction::DOWN)
			alEffecti(effect, AL_FREQUENCY_SHIFTER_RIGHT_DIRECTION, AL_FREQUENCY_SHIFTER_DIRECTION_DOWN);
		else
			alEffecti(effect, AL_FREQUENCY_SHIFTER_RIGHT_DIRECTION, AL_FREQUENCY_SHIFTER_DEFAULT_RIGHT_DIRECTION);
		break;
	}
	case Type::MORPHER:
	{
		Waveform wave = static_cast<Waveform>(getValue(Parameter::MORPHER_WAVEFORM, static_cast<int>(Waveform::MAX_ENUM)));
		if (wave == Waveform::SINE)
			alEffecti(effect, AL_VOCAL_MORPHER_WAVEFORM, AL_VOCAL_MORPHER_WAVEFORM_SINUSOID);
		else if (wave == Waveform::TRIANGLE)
			alEffecti(effect, AL_VOCAL_MORPHER_WAVEFORM, AL_VOCAL_MORPHER_WAVEFORM_TRIANGLE);
		else if (wave == Waveform::SAWTOOTH)
			alEffecti(effect, AL_VOCAL_MORPHER_WAVEFORM, AL_VOCAL_MORPHER_WAVEFORM_SAWTOOTH);
		else
			alEffecti(effect, AL_VOCAL_MORPHER_WAVEFORM, AL_VOCAL_MORPHER_DEFAULT_WAVEFORM);

		Phoneme phoneme = static_cast<Phoneme>(getValue(Parameter::MORPHER_PHONEMEA, static_cast<int>(Phoneme::MAX_ENUM)));
		if (phoneme == Phoneme::MAX_ENUM)
			alEffecti(effect, AL_VOCAL_MORPHER_PHONEMEA, AL_VOCAL_MORPHER_DEFAULT_PHONEMEA);
		else
			alEffecti(effect, AL_VOCAL_MORPHER_PHONEMEA, phonemeMap[phoneme]);

		phoneme = static_cast<Phoneme>(getValue(Parameter::MORPHER_PHONEMEB, static_cast<int>(Phoneme::MAX_ENUM)));
		if (phoneme == Phoneme::MAX_ENUM)
			alEffecti(effect, AL_VOCAL_MORPHER_PHONEMEB, AL_VOCAL_MORPHER_DEFAULT_PHONEMEB);
		else
			alEffecti(effect, AL_VOCAL_MORPHER_PHONEMEB, phonemeMap[phoneme]);

		alEffectf(PARAMSTR(MORPHER_RATE,VOCAL_MORPHER,RATE));
		alEffecti(PARAMSTR(MORPHER_TUNEA,VOCAL_MORPHER,PHONEMEA_COARSE_TUNING));
		alEffecti(PARAMSTR(MORPHER_TUNEB,VOCAL_MORPHER,PHONEMEB_COARSE_TUNING));
		break;
	}
	case Type::PITCHSHIFTER:
	{
		constexpr float default_tune = AL_PITCH_SHIFTER_DEFAULT_COARSE_TUNE + AL_PITCH_SHIFTER_DEFAULT_FINE_TUNE / 100.0;
		const float tune = getValue(Parameter::PITCHSHIFTER_PITCH, default_tune);
		const float rem = std::remainder(tune, 1.0f);
		int fine = (int)(rem * 100);
		int coarse = (int)std::round(tune - rem);
		if (coarse > AL_PITCH_SHIFTER_MAX_COARSE_TUNE)
		{
			coarse = AL_PITCH_SHIFTER_MAX_COARSE_TUNE;
			fine = AL_PITCH_SHIFTER_MAX_FINE_TUNE;
		}
		else if (coarse < AL_PITCH_SHIFTER_MIN_COARSE_TUNE)
		{
			coarse = AL_PITCH_SHIFTER_MIN_COARSE_TUNE;
			fine = AL_PITCH_SHIFTER_MIN_FINE_TUNE;
		}
		alEffecti(effect, AL_PITCH_SHIFTER_COARSE_TUNE, coarse);
		alEffecti(effect, AL_PITCH_SHIFTER_FINE_TUNE, fine);
		break;
	}
	case Type::MODULATOR:
	{
		Waveform wave = static_cast<Waveform>(getValue(Parameter::MODULATOR_WAVEFORM, static_cast<int>(Waveform::MAX_ENUM)));
		if (wave == Waveform::SINE)
			alEffecti(effect, AL_RING_MODULATOR_WAVEFORM, AL_RING_MODULATOR_SINUSOID);
		else if (wave == Waveform::SAWTOOTH)
			alEffecti(effect, AL_RING_MODULATOR_WAVEFORM, AL_RING_MODULATOR_SAWTOOTH);
		else if (wave == Waveform::SQUARE)
			alEffecti(effect, AL_RING_MODULATOR_WAVEFORM, AL_RING_MODULATOR_SQUARE);
		else
			alEffecti(effect, AL_RING_MODULATOR_WAVEFORM, AL_RING_MODULATOR_DEFAULT_WAVEFORM);

		alEffectf(PARAMSTR(MODULATOR_FREQ, RING_MODULATOR, FREQUENCY));
		alEffectf(PARAMSTR(MODULATOR_HIGHCUT, RING_MODULATOR, HIGHPASS_CUTOFF));
		break;
	}

	case Type::AUTOWAH:
		alEffectf(PARAMSTR(AUTOWAH_ATTACK,AUTOWAH,ATTACK_TIME));
		alEffectf(PARAMSTR(AUTOWAH_RELEASE,AUTOWAH,RELEASE_TIME));
		alEffectf(PARAMSTR(AUTOWAH_RESONANCE,AUTOWAH,RESONANCE));
		alEffectf(PARAMSTR(AUTOWAH_PEAKGAIN,AUTOWAH,PEAK_GAIN));
		break;

	case Type::COMPRESSOR:
		alEffecti(effect, AL_COMPRESSOR_ONOFF, getValue(Parameter::COMPRESSOR_ENABLE, static_cast<int>(AL_COMPRESSOR_DEFAULT_ONOFF)));
		break;

	case Type::EQUALIZER:
		alEffectf(PARAMSTR(EQUALIZER_LOWGAIN, EQUALIZER, LOW_GAIN));
		alEffectf(PARAMSTR(EQUALIZER_LOWCUT, EQUALIZER, LOW_CUTOFF));
		alEffectf(PARAMSTR(EQUALIZER_MID1GAIN, EQUALIZER, MID1_GAIN));
		alEffectf(PARAMSTR(EQUALIZER_MID1FREQ, EQUALIZER, MID1_CENTER));
		alEffectf(PARAMSTR(EQUALIZER_MID1BAND, EQUALIZER, MID1_WIDTH));
		alEffectf(PARAMSTR(EQUALIZER_MID2GAIN, EQUALIZER, MID2_GAIN));
		alEffectf(PARAMSTR(EQUALIZER_MID2FREQ, EQUALIZER, MID2_CENTER));
		alEffectf(PARAMSTR(EQUALIZER_MID2BAND, EQUALIZER, MID2_WIDTH));
		alEffectf(PARAMSTR(EQUALIZER_HIGHGAIN, EQUALIZER, HIGH_GAIN));
		alEffectf(PARAMSTR(EQUALIZER_HIGHCUT, EQUALIZER, HIGH_CUTOFF));
		break;
	case Type::BASIC:
	case Type::MAX_ENUM:
		break;
	default: ;
	}
#undef PARAMSTR
#undef clampf
	//alGetError();

	return true;
#else
	return false;
#endif //ALC_EXT_EFX
}

const AudioEffect::ParamMap& AudioEffect::getParams() const
{
	return params;
}

float AudioEffect::getValue(Parameter in, float def) const
{
	return params.find(in) == params.end() ? def : params.at(in);
}

int AudioEffect::getValue(Parameter in, int def) const
{
	return params.find(in) == params.end() ? def : static_cast<int>(params.at(in));
}


std::map<AudioEffect::Phoneme, ALint> AudioEffect::phonemeMap =
{
	{AudioEffect::Phoneme::A, AL_VOCAL_MORPHER_PHONEME_A},
	{AudioEffect::Phoneme::E, AL_VOCAL_MORPHER_PHONEME_E},
	{AudioEffect::Phoneme::I, AL_VOCAL_MORPHER_PHONEME_I},
	{AudioEffect::Phoneme::O, AL_VOCAL_MORPHER_PHONEME_O},
	{AudioEffect::Phoneme::U, AL_VOCAL_MORPHER_PHONEME_U},
	{AudioEffect::Phoneme::AA, AL_VOCAL_MORPHER_PHONEME_AA},
	{AudioEffect::Phoneme::AE, AL_VOCAL_MORPHER_PHONEME_AE},
	{AudioEffect::Phoneme::AH, AL_VOCAL_MORPHER_PHONEME_AH},
	{AudioEffect::Phoneme::AO, AL_VOCAL_MORPHER_PHONEME_AO},
	{AudioEffect::Phoneme::EH, AL_VOCAL_MORPHER_PHONEME_EH},
	{AudioEffect::Phoneme::ER, AL_VOCAL_MORPHER_PHONEME_ER},
	{AudioEffect::Phoneme::IH, AL_VOCAL_MORPHER_PHONEME_IH},
	{AudioEffect::Phoneme::IY, AL_VOCAL_MORPHER_PHONEME_IY},
	{AudioEffect::Phoneme::UH, AL_VOCAL_MORPHER_PHONEME_UH},
	{AudioEffect::Phoneme::UW, AL_VOCAL_MORPHER_PHONEME_UW},
	{AudioEffect::Phoneme::B, AL_VOCAL_MORPHER_PHONEME_B},
	{AudioEffect::Phoneme::D, AL_VOCAL_MORPHER_PHONEME_D},
	{AudioEffect::Phoneme::F, AL_VOCAL_MORPHER_PHONEME_F},
	{AudioEffect::Phoneme::G, AL_VOCAL_MORPHER_PHONEME_G},
	{AudioEffect::Phoneme::J, AL_VOCAL_MORPHER_PHONEME_J},
	{AudioEffect::Phoneme::K, AL_VOCAL_MORPHER_PHONEME_K},
	{AudioEffect::Phoneme::L, AL_VOCAL_MORPHER_PHONEME_L},
	{AudioEffect::Phoneme::M, AL_VOCAL_MORPHER_PHONEME_M},
	{AudioEffect::Phoneme::N, AL_VOCAL_MORPHER_PHONEME_N},
	{AudioEffect::Phoneme::P, AL_VOCAL_MORPHER_PHONEME_P},
	{AudioEffect::Phoneme::R, AL_VOCAL_MORPHER_PHONEME_R},
	{AudioEffect::Phoneme::S, AL_VOCAL_MORPHER_PHONEME_S},
	{AudioEffect::Phoneme::T, AL_VOCAL_MORPHER_PHONEME_T},
	{AudioEffect::Phoneme::V, AL_VOCAL_MORPHER_PHONEME_V},
	{AudioEffect::Phoneme::Z, AL_VOCAL_MORPHER_PHONEME_Z}
};

NS_CC_END
