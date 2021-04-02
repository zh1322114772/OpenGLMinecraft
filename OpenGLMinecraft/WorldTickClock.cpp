#include "WorldTickClock.hpp"

namespace tickerable
{
	WorldTickClock::WorldTickClock(const float interval) : TickClock(interval)
	{
		//add tasks
		inputGetter = new tasks::InputGetter();
		addTask(inputGetter);

		chunkLoader = new tasks::ChunkLoader(32, 12344321);
		addTask(chunkLoader);

		gameLogic = new tasks::GameLogic();
		addTask(gameLogic);

		physicsEngine = new tasks::PhysicsEngine(32, interval);
		addTask(physicsEngine);

		outputGetter = new tasks::OutputGetter(32);
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

	tasks::PhysicsEngine* WorldTickClock::getPhysicsEngine() 
	{
		return physicsEngine;
	}

	tasks::GameLogic* WorldTickClock::getLogic() 
	{
		return gameLogic;
	}


	WorldTickClock::~WorldTickClock() 
	{

	}
}