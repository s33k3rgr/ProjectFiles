#include "Clock.h"

namespace Timing
{

	bool  Clock::initialize()
	{

		return ( gettimeofday(&lastStartTime, 0) == 0 );
	}

	bool  Clock::shutdown()
	{
		return true;
	}


	void  Clock::lap()
	{
	   stop();
	   start();
	}


	float Clock::lastLapTime() const
	{
		return deltaTime;
	}


	void Clock::start()
	{
        gettimeofday(&lastStartTime, 0);
	}


    void Clock::stop()
    {
        timeval thisTime;
        gettimeofday(&thisTime, 0);
        float fSeconds = (float)(thisTime.tv_sec - lastStartTime.tv_sec);
        float fFraction = (float)(thisTime.tv_usec - lastStartTime.tv_usec) * 0.000001f;
        deltaTime = fSeconds + fFraction;
        lastStartTime = thisTime;
    }


}
