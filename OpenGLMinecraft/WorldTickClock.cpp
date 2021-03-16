#include "WorldTickClock.hpp"

namespace tickerable
{
	WorldTickClock::WorldTickClock(const float interval) : TickClock(interval)
	{
		//add tasks
		inputGetter = new tasks::InputGetter();
		addTask(inputGetter);

		chunkLoader = new tasks::ChunkLoader(7, 5302000);
		addTask(chunkLoader);
	}

	tasks::InputGetter* WorldTickClock::getInputGetter() 
	{
		return inputGetter;
	}

	tasks::ChunkLoader* WorldTickClock::getChunkLoader() 
	{
		return chunkLoader;
	}

	WorldTickClock::~WorldTickClock() 
	{
		delete inputGetter;
		delete chunkLoader;
	}
}