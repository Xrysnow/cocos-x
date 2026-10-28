#pragma once
#include "platform/CCPlatformMacros.h"
#include "AudioCommon.h"
#include <string>
#include <vector>
#include <map>

#ifndef AL_FILTER_NULL
#define AL_FILTER_NULL (0)
#endif

NS_CC_BEGIN
	class CC_DLL AudioFilter
	{
	public:
		enum class Type
		{
			BASIC,
			LOWPASS,
			HIGHPASS,
			BANDPASS,
			MAX_ENUM
		};

		enum class Parameter
		{
			TYPE,
			VOLUME,

			LOWGAIN,  // HIGHPASS, BANDPASS
			HIGHGAIN, // LOWPASS, BANDPASS

			MAX_ENUM
		};

		using ParamMap = std::map<Parameter, float>;

		AudioFilter();
		AudioFilter(const AudioFilter &s);
		virtual ~AudioFilter();
		Type getType() const;

		virtual AudioFilter* clone();
		ALuint getFilter() const;
		virtual bool setParams(const ParamMap& params);
		virtual const ParamMap& getParams() const;

	protected:
		Type type;
		bool generateFilter() const;
		void deleteFilter() const;
		bool applyParams() const;
		float getValue(Parameter in, float def) const;
		int getValue(Parameter in, int def) const;
		mutable ALuint filter = AL_FILTER_NULL;
		mutable int filterGeneration = -1;
		ParamMap params;
	};	
NS_CC_END
