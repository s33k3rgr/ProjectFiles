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
		//void newFrame();
		void lap();
		//float timeElapsedLastFrame() const;
		float lastLapTime() const;
	};
}


#endif
