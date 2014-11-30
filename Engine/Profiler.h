#ifndef DEBUG_PROFILER_H
#define DEBUG_PROFILER_H
#include "TypeDefs.h"

namespace Profiling
{
	class Profiler
	{

	public:
		static const je::uint MAX_FRAME_SAMPLES = 1000;
		static Profiler& getInstance();
	private:

		Profiler() {}
		Profiler(const Profiler&);
		Profiler& operator=(const Profiler&);
		static Profiler theInstance;
#if PROFILING_ON
		bool status;
		const char* fileName;
		static const je::uint MAX_PROFILE_CATEGORIES = 20;
		je::uint frameIndex;
		je::uint categoryIndex;
		je::uint numUsedCategories;
		struct ProfileCategory
		{
			const char* name;
			float samples[MAX_FRAME_SAMPLES];
		} categories[MAX_PROFILE_CATEGORIES];

		bool wrapped() const;
		void writeFrame(je::uint frameNumber) const;
		bool currentFrameComplete() const;
		char getDelimiter(je::uint index) const;
		void checkForDuplicateCategory(const char* category);
#endif
	public:
#if PROFILING_ON
		void newFrame();
		void shutdown();
		void initialize(const char* fileName);
		void addEntry(const char* category, float time);
		void checkStatus(bool *status);
#else
		void newFrame() {}
		void shutdown() {}
		void initialize(const char* fileName) {}
		void addEntry(const char* category, float time) {}
		void checkStatus(bool *status) {}
#endif
	};
}


#define profiler Profiling::Profiler::getInstance()

#endif
