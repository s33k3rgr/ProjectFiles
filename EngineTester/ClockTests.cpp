#include <gtest/gtest.h>
#include <Clock.h>
#include <unistd.h>

using Timing::Clock;

TEST(Clock, Initialize)
{
	Clock clock;
	EXPECT_TRUE(clock.initialize());
	EXPECT_TRUE(clock.shutdown());
}

TEST(Clock, FrameTimeMeasuring)
{
	Clock clock;
	EXPECT_TRUE(clock.initialize());
	usleep(1000000);    //Sleep for one second
	clock.lap();
	float timedTime  = clock.lastLapTime();
	EXPECT_TRUE(0.9f < timedTime && timedTime < 1.1f);
	clock.lap();
	usleep(500000);
	clock.lap();
	timedTime = clock.lastLapTime();
	EXPECT_TRUE(0.4f < timedTime && timedTime < 0.6f);
#ifdef OVERNIGHT_TESTS
	const int NUM_TESTS = 10 + rand() % 100;
	const float THRESHOLD = 0.01f;
	for (int i = 0; i < NUM_TESTS; i++)
	{
		int thisTestTimeMilliseconds = rand() % 10000;
		float thisTestTimeSeconds = thisTestTimeMilliseconds / 1000.0f;
		clock.lap();
		usleep(thisTestTimeMilliseconds * 1000);
		clock.lap();
		float elapsedSeconds = clock.lastLapTime();
		EXPECT_TRUE((thisTestTimeSeconds - THRESHOLD) < elapsedSeconds);
		EXPECT_TRUE((thisTestTimeSeconds + THRESHOLD) > elapsedSeconds);
	}

#endif // OVERNIGHT_TESTS
	clock.lap();

	EXPECT_TRUE(clock.shutdown());
}
