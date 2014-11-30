#ifndef ENGINE_CLOCK_H
#define ENGINE_CLOCK_H
#include <sys/time.h>

namespace Timing
{
	class Clock
	{
	    timeval timeFrequency;
		timeval lastStartTime;
		float deltaTime;
	public:
		bool initialize();
		bool shutdown();
		void start();
		void stop();
		void lap();
		float lastLapTime() const;
	};
}


#endif
