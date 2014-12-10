#ifndef ENGINE_GAME_CLOCK_H
#define ENGINE_GAME_CLOCK_H
#include "Clock.h"


namespace Timing
{
	class GameClock
	{
		Clock clock;
		GameClock() {};
		GameClock(const GameClock&);
		GameClock& operator=(const GameClock&);
		static GameClock instance;
	public:
		bool initialize();
		bool shutdown();
		void newFrame();
		float dt() const;
		static GameClock& getInstance();
	};
#define gameClock Timing::GameClock::getInstance()
}

#endif

