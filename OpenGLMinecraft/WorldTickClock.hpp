#pragma once
#include "TickClock.hpp"
#include "TKB_InputGetter.hpp"
#include "TKB_ChunkLoader.hpp"
#include "TKB_OutputGetter.hpp"
#include "TKB_PhysicsEngine.hpp"
#include "TKB_Logic.hpp"
namespace tickerable
{
	/// <summary>
	/// dedicated tick clock for world event processing
	/// </summary>
	class WorldTickClock : public TickClock
	{
	private:
		/// <summary>
		/// deliver inputs to other tasks
		/// </summary>
		tasks::InputGetter* inputGetter;
		
		/// <summary>
		/// chunk loader that load chunks
		/// </summary>
		tasks::ChunkLoader* chunkLoader;

		/// <summary>
		/// game physics engine
		/// </summary>
		tasks::PhysicsEngine* physicsEngine;

		/// <summary>
		/// process game logic
		/// </summary>
		tasks::GameLogic* gameLogic;

		/// <summary>
		/// deliver outputs to render thread
		/// </summary>
		tasks::OutputGetter* outputGetter;

	public:

		/// <summary>
		/// constructor
		/// </summary>
		/// <param name="interval">interval in millisecond</param>
		/// <returns></returns>
		WorldTickClock(const float interval);

		~WorldTickClock();

		/// <summary>
		/// get input getter pointer
		/// </summary>
		/// <returns></returns>
		tasks::InputGetter* getInputGetter();

		/// <summary>
		/// get chunk loader pointer
		/// </summary>
		/// <returns></returns>
		tasks::ChunkLoader* getChunkLoader();

		/// <summary>
		/// get ouput getter pointer
		/// </summary>
		/// <returns></returns>
		tasks::OutputGetter* getOutputGetter();

		/// <summary>
		/// get physics engine
		/// </summary>
		/// <returns></returns>
		tasks::PhysicsEngine* getPhysicsEngine();

		/// <summary>
		/// get game logic class
		/// </summary>
		/// <returns></returns>
		tasks::GameLogic* getLogic();
	};


}