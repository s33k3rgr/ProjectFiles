#include <gtest/gtest.h>
#include "Profiler.h"
#include <iostream>
#include <fstream>
#include "TypeDefs.h"
using std::ifstream;
using std::string;
using Profiling::Profiler;
using je::uint;

namespace
{

	char* categories[] =
	{
		"Category1",
		"Category2",
		"Category3"
	};
	const char* const PROFILE_FILE_NAME = "profiles.csv";
	const uint NUM_CATEGORIES = sizeof(categories) / sizeof(*categories);

	string getNextToken(ifstream& theFile)
{
	char c;
	string ret;
	while(theFile.good())
	{
		theFile >> std::noskipws;
		theFile >> c;
		if(c == ',' || c == '\n')
			break;
		ret += c;
	}
	return ret;
}

	void writeFrames(uint numFrames)
{
	float sampleNumber = 0;
	for(float frame = 0; frame < numFrames; frame++)
	{
		profiler.newFrame();
		for(uint cat = 0; cat < NUM_CATEGORIES; cat++)
		{
			profiler.addEntry(categories[cat], sampleNumber++);
		}

	}

}

	bool isAtEndOfFile(ifstream& input)
{
	if(!input.good())
		return false;
	char bitBucket;
	input >> bitBucket;
	return !input.good();
}

	void checkFrames(uint numFrames, bool excludeLastFrame = false)
{
	ifstream input(PROFILE_FILE_NAME);

	for(uint i = 0; i < NUM_CATEGORIES; i++)
	{
		EXPECT_EQ(getNextToken(input), categories[i]);
	}

	uint profileNumber = 0;
	if(numFrames >= Profiler::MAX_FRAME_SAMPLES)
	{
		profileNumber = (numFrames - Profiler::MAX_FRAME_SAMPLES) * NUM_CATEGORIES;
		numFrames = Profiler::MAX_FRAME_SAMPLES;
	}

	if(excludeLastFrame)
	{
		profileNumber += NUM_CATEGORIES;
		numFrames--;
	}

	for(uint i = 0; i < (numFrames * NUM_CATEGORIES); i++)
	{
		string buf = getNextToken(input);
		EXPECT_EQ(atoi(buf.c_str()), profileNumber++);
	}
	EXPECT_TRUE(isAtEndOfFile(input));
}


	void runTestsOnFrames(uint numFrames)
	{
		profiler.initialize(PROFILE_FILE_NAME);
		writeFrames(numFrames);
		profiler.shutdown();
		checkFrames(numFrames);
	}

	void writeIncompleteFrames(uint numFrames)
	{
		bool wrapped = numFrames >= Profiler::MAX_FRAME_SAMPLES;
		profiler.initialize(PROFILE_FILE_NAME);
		writeFrames(numFrames);
		profiler.newFrame();
		profiler.addEntry(categories[0], 15);
		profiler.shutdown();
		checkFrames(numFrames,wrapped);
	}
}

TEST(Profiler, SmallAmountOfFrames)
{
	runTestsOnFrames(5);
}

TEST(Profiler, ExcludeIncompleteFrames)
{
	writeIncompleteFrames(Profiler::MAX_FRAME_SAMPLES - 2); // Not wrap
	writeIncompleteFrames(Profiler::MAX_FRAME_SAMPLES + 2); // wrap
}

TEST(Profiler, LargeAmountOfFramesNonCircular)
{
	const uint NUM_FRAMES_THIS_TEST =
		static_cast<uint>(Profiler::MAX_FRAME_SAMPLES * .8);
	runTestsOnFrames(NUM_FRAMES_THIS_TEST);
}

TEST(Profiler, ArrayBoundaries)
{
	runTestsOnFrames(Profiler::MAX_FRAME_SAMPLES);
	runTestsOnFrames(Profiler::MAX_FRAME_SAMPLES + 1);
	runTestsOnFrames(Profiler::MAX_FRAME_SAMPLES + 2);
}

TEST(Profiler, CirculatingOnePlusSome)
{
	runTestsOnFrames(static_cast<uint>(Profiler::MAX_FRAME_SAMPLES + 3));
}

TEST(Profiler, GoAroundSeveralTimes)
{
	runTestsOnFrames(static_cast<uint>(Profiler::MAX_FRAME_SAMPLES * 3.14));
}

TEST(Profiler, AddingDuplicateCategoriesInOneFrame)
{
	profiler.initialize(PROFILE_FILE_NAME);
	profiler.newFrame();
	profiler.addEntry("My First Category", 1);
	profiler.addEntry("My Second Category", 2);
	bool status;
	profiler.checkStatus(&status);
	EXPECT_TRUE(status);
	profiler.addEntry("My First Category", 2);
	profiler.checkStatus(&status);
	EXPECT_TRUE(!status);
	profiler.shutdown();
}
