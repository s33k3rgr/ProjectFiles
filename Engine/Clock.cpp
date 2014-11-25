#include "Clock.h"

namespace Timing
{

	bool  Clock::initialize()
	{

		return ( gettimeofday(&timeLastFrame, 0) == 0 );
	}

	bool  Clock::shutdown()
	{
		return true;
	}


	void  Clock::newFrame()
	{
	    timeval thisTime;
        gettimeofday(&thisTime, 0);
        float fSeconds = (float)(thisTime.tv_sec - timeLastFrame.tv_sec);
        float fFraction = (float)(thisTime.tv_usec - timeLastFrame.tv_usec) * 0.000001f;
        deltaTime = fSeconds + fFraction;
        timeLastFrame = thisTime;
	}


	float Clock::timeElapsedLastFrame() const
	{
		return deltaTime;
	}

}
