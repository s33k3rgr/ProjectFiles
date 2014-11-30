#ifndef DEBUG_PROFILE_H
#define DEBUG_PROFILE_H
#if PROFILING_ON
#include "Clock.h"
#endif

namespace Profiling
{
	class Profile
	{
#if PROFILING_ON
		const char* category;
		Timing::Clock clock;
#endif
	public:
#if PROFILING_ON
		Profile(const char* category);
		~Profile();
#else
		Profile(const char* category) {}
		~Profile() {}
#endif
	};
}

#if PROFILING_ON
#define PROFILE(category) Profiling::Profile p(category)
#else
#define PROFILE(category)
#endif

#endif
