#pragma once
#include "platform/CCPlatformMacros.h"
#include "AudioCommon.h"
#include "base/CCRef.h"
#include <map>
#ifdef ECHO
#undef ECHO
#endif

NS_CC_BEGIN
	class CC_DLL AudioEffect : public cocos2d::Ref
	{
	public:
		enum class Type
		{
			BASIC,			// not a real type
			REVERB,
			CHORUS,			// implemented in openal-soft-1.16.0
			DISTORTION,		// implemented in openal-soft-1.16.0
			ECHO,
			FLANGER,		// implemented in openal-soft-1.16.0
			FREQSHIFTER,	// implemented in openal-soft-1.19.0
			MORPHER,		// not implemented yet
			PITCHSHIFTER,	// implemented in openal-soft-1.19.0
			MODULATOR,
			AUTOWAH,		// implemented in openal-soft-1.19.0
			COMPRESSOR,		// implemented in openal-soft-1.16.0
			EQUALIZER,		// implemented in openal-soft-1.16.0
			MAX_ENUM
		};

		enum class Parameter
		{
			TYPE,
			VOLUME,

			// [0.0, 1.0], 0.32
			REVERB_GAIN,
			// [0.0, 1.0], 0.89
			REVERB_HFGAIN,
			// [0.0, 1.0], 1.0
			REVERB_DENSITY,
			// [0.0, 1.0], 1.0
			REVERB_DIFFUSION,
			// [0.1, 20.0], 1.49
			REVERB_DECAY,
			// [0.1, 2.0], 0.83
			REVERB_HFDECAY,
			// [0.0, 3.16], 0.05
			REVERB_EARLYGAIN,
			// [0.0, 0.3], 0.007
			REVERB_EARLYDELAY,
			// [0.0, 10.0], 1.26
			REVERB_LATEGAIN,
			// [0.0, 0.1], 0.011
			REVERB_LATEDELAY,
			// [0.0, 10.0], 0.0
			REVERB_ROLLOFF,
			// [0.892, 1.0], 0.994
			REVERB_AIRHFGAIN,
			// [AL_FALSE, AL_TRUE], AL_TRUE
			REVERB_HFLIMITER,

			CHORUS_WAVEFORM,
			// [-180, 180], 90
			CHORUS_PHASE,
			// [0.0, 10.0], 1.1
			CHORUS_RATE,
			// [0.0, 1.0], 0.1
			CHORUS_DEPTH,
			// [-1.0, 1.0], 0.25
			CHORUS_FEEDBACK,
			// [0.0, 0.016], 0.016
			CHORUS_DELAY,

			// [0.01, 1.0], 0.05
			DISTORTION_GAIN,
			// [0.0, 1.0], 0.2
			DISTORTION_EDGE,
			// [80.0, 24000.0], 8000.0
			DISTORTION_LOWCUT,
			// [80.0, 24000.0], 3600.0
			DISTORTION_EQCENTER,
			// [80.0, 24000.0], 3600.0
			DISTORTION_EQBAND,

			// [0.0, 0.207], 0.1
			ECHO_DELAY,
			// [0.0, 0.404], 0.1
			ECHO_LRDELAY,
			// [0.0, 0.99], 0.5
			ECHO_DAMPING,
			// [0.0, 1.0], 0.5
			ECHO_FEEDBACK,
			// [-1.0, 1.0], -1.0
			ECHO_SPREAD,

			FLANGER_WAVEFORM,
			// [-180, 180], 0
			FLANGER_PHASE,
			// [0.0, 10.0], 0.27
			FLANGER_RATE,
			// [0.0, 1.0], 1.0
			FLANGER_DEPTH,
			// [-1.0, 1.0], -0.5
			FLANGER_FEEDBACK,
			// [0.0, 0.004], 0.002
			FLANGER_DELAY,

			// [0.0, 24000.0], 0.0
			FREQSHIFTER_FREQ,
			FREQSHIFTER_LEFTDIR,
			FREQSHIFTER_RIGHTDIR,

			MORPHER_WAVEFORM,
			// [0.0, 10.0], 1.41
			MORPHER_RATE,
			MORPHER_PHONEMEA,
			MORPHER_PHONEMEB,
			// [-24, 24], 0
			MORPHER_TUNEA,
			// [-24, 24], 0
			MORPHER_TUNEB,

			// [-12, 12], 12
			PITCHSHIFTER_PITCH,

			MODULATOR_WAVEFORM,
			// [0.0, 8000.0], 440.0
			MODULATOR_FREQ,
			// [0.0, 24000.0], 800.0
			MODULATOR_HIGHCUT,

			// [0.0001, 1.0], 0.06
			AUTOWAH_ATTACK,
			// [0.0001, 1.0], 0.06
			AUTOWAH_RELEASE,
			// [2.0, 1000.0], 1000.0
			AUTOWAH_RESONANCE,
			// [0.00003, 31621.0], 11.22
			AUTOWAH_PEAKGAIN,

			// [AL_FALSE, AL_TRUE], AL_TRUE
			COMPRESSOR_ENABLE,

			// [0.126, 7.943], 1.0
			EQUALIZER_LOWGAIN,
			// [50.0, 800.0], 200.0
			EQUALIZER_LOWCUT,
			// [0.126, 7.943], 1.0
			EQUALIZER_MID1GAIN,
			// [200.0, 3000.0], 500.0
			EQUALIZER_MID1FREQ,
			// [0.01, 1.0], 1.0
			EQUALIZER_MID1BAND,
			// [0.126, 7.943], 1.0
			EQUALIZER_MID2GAIN,
			// [1000.0, 8000.0], 3000.0
			EQUALIZER_MID2FREQ,
			// [0.01, 1.0], 1.0
			EQUALIZER_MID2BAND,
			// [0.126, 7.943], 1.0
			EQUALIZER_HIGHGAIN,
			// [4000.0, 16000.0], 6000.0
			EQUALIZER_HIGHCUT,

			MAX_ENUM
		};
/*
		enum ParameterType
		{
			PARAM_TYPE,
			PARAM_FLOAT,
			PARAM_BOOL,
			PARAM_WAVEFORM,
			PARAM_DIRECTION,
			PARAM_PHONEME,
			PARAM_MAX_ENUM
		};
*/
		// TYPE_CHORUS: CHORUS_WAVEFORM
		// TYPE_FLANGER: FLANGER_WAVEFORM
		// TYPE_MORPHER: MORPHER_WAVEFORM
		enum class Waveform
		{
			SINE,
			TRIANGLE,
			SAWTOOTH,
			SQUARE,
			MAX_ENUM
		};

		// TYPE_FREQSHIFTER: FREQSHIFTER_LEFTDIR, FREQSHIFTER_RIGHTDIR
		enum class Direction
		{
			NONE,
			UP,
			DOWN,
			MAX_ENUM
		};

		// TYPE_MORPHER: MORPHER_PHONEMEA, MORPHER_PHONEMEB
		enum class Phoneme
		{
			A,
			E,
			I,
			O,
			U,
			AA,
			AE,
			AH,
			AO,
			EH,
			ER,
			IH,
			IY,
			UH,
			UW,
			B,
			D,
			F,
			G,
			J,
			K,
			L,
			M,
			N,
			P,
			R,
			S,
			T,
			V,
			Z,
			MAX_ENUM
		};

		using ParamMap = std::map<Parameter, float>;

		AudioEffect();
		AudioEffect(const AudioEffect &s);
		virtual ~AudioEffect();
		virtual AudioEffect *clone();
		ALuint getEffect() const;
		virtual bool setParams(const ParamMap& params);
		virtual const ParamMap& getParams() const;

	private:
		bool generateEffect();
		void deleteEffect();
		float getValue(Parameter in, float def) const;
		int getValue(Parameter in, int def) const;

		Type type;
		ALuint effect = AL_EFFECT_NULL;
		ParamMap params;
		static std::map<Phoneme, ALint> phonemeMap;
	};	
NS_CC_END
