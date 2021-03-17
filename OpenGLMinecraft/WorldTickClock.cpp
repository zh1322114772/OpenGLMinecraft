#include "WorldTickClock.hpp"

namespace tickerable
{
	WorldTickClock::WorldTickClock(const float interval) : TickClock(interval)
	{
		//add tasks
		inputGetter = new tasks::InputGetter();
		addTask(inputGetter);

		chunkLoader = new tasks::ChunkLoader(12, 5302000);
		addTask(chunkLoader);

		outputGetter = new tasks::OutputGetter(12);
		addTask(outputGetter);
	}

	tasks::InputGetter* WorldTickClock::getInputGetter() 
	{
		return inputGetter;
	}

	tasks::ChunkLoader* WorldTickClock::getChunkLoader() 
	{
		return chunkLoader;
	}

	tasks::OutputGetter* WorldTickClock::getOutputGetter() 
	{
		return outputGetter;
	}

	WorldTickClock::~WorldTickClock() 
	{
		delete inputGetter;
		delete chunkLoader;
		delete outputGetter;
	}
}