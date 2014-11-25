#ifndef ENGINE_CLOCK_H
#define ENGINE_CLOCK_H
#include <sys/time.h>

namespace Timing
{
	class Clock
	{
	    timeval timeFrequency;
		timeval timeLastFrame;
		float deltaTime;
	public:
		bool initialize();
		bool shutdown();
		void newFrame();
		float timeElapsedLastFrame() const;
	};
}


#endif
