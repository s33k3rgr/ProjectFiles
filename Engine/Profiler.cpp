#include "Profiler.h"
#ifdef PROFILING_ON
#include <cassert>
#include <fstream>
#include <string.h>
#endif


using je::uint;

namespace Profiling
{

	Profiler Profiler::theInstance;

	Profiler& Profiler::getInstance()
	{
		return theInstance;
	}

#ifdef PROFILING_ON

	static std::ofstream outStream;

	void Profiler::addEntry(const char* category, float time)
	{

		assert(categoryIndex < MAX_PROFILE_CATEGORIES);
		ProfileCategory& pc = categories[categoryIndex];

		if(frameIndex == 0)
		{
			pc.name = category;
			numUsedCategories++;
			checkForDuplicateCategory(category);
		}
		else
		{
			assert(categoryIndex < numUsedCategories);
			assert(pc.name == category && category != NULL);
		}
		categoryIndex++;
		pc.samples[frameIndex % MAX_FRAME_SAMPLES] = time;
	}

	void Profiler::newFrame()
	{
		assert(status);
		if(frameIndex > 0)
			assert(categoryIndex == numUsedCategories);
		frameIndex++;
		categoryIndex = 0;
	}

	void Profiler::shutdown()
	{
		outStream.open(fileName, std::ios::trunc);

		for(uint i = 0; i < numUsedCategories; i++)
		{
			outStream << categories[i].name;
			outStream << getDelimiter(i);
		}

		uint endIndex;
		uint startIndex;

		if(wrapped())
		{
			uint endIndex = frameIndex % MAX_FRAME_SAMPLES;
			uint startIndex = (endIndex + 1) % MAX_FRAME_SAMPLES;
			while(startIndex != endIndex)
			{
				writeFrame(startIndex);
				startIndex = (startIndex + 1) % MAX_FRAME_SAMPLES;
			}
			if(currentFrameComplete())
				writeFrame(startIndex);
		}
		else
		{
			uint numActualFrames = frameIndex;
			if(currentFrameComplete())
				numActualFrames++;
			startIndex = 0;
			endIndex = numActualFrames;
			while(startIndex < endIndex)
			{
				writeFrame(startIndex++);
			}
		}

		outStream.close();

	}

	void Profiler::writeFrame(uint frameNumber) const
	{
		for(uint cat = 0; cat < numUsedCategories; cat++)
		{
			outStream << categories[cat].samples[frameNumber];
			outStream << getDelimiter(cat);
		}
	}

	void Profiler::initialize(const char* fileName)
	{
		status = true;
		this->fileName = fileName;
		frameIndex = -1;
		categoryIndex = 0;
		numUsedCategories = 0;
	}

	char Profiler::getDelimiter(uint index) const
	{
		return ((index + 1) < numUsedCategories) ? ',' : '\n';
	}

	bool Profiler::wrapped() const
	{
		return frameIndex >= MAX_FRAME_SAMPLES && frameIndex != -1;
	}

	bool Profiler::currentFrameComplete() const
	{
		return categoryIndex == numUsedCategories;
	}

	void Profiler::checkStatus(bool *status)
	{
		*status = this->status;
	}

	void Profiler::checkForDuplicateCategory(const char* category)
	{
		for(uint i = 0; i < categoryIndex; i++)
			status &= (strcmp(categories[i].name, category) != 0);
	}

#endif
}

