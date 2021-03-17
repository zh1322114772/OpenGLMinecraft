#pragma once
#include "TickClock.hpp"
#include "TKB_InputGetter.hpp"
#include "TKB_ChunkLoader.hpp"
#include "TKB_OutputGetter.hpp"

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
	};


}