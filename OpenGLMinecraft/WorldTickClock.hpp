#pragma once
#include "TickClock.hpp"
#include "TKB_InputGetter.hpp"
#include "TKB_ChunkLoader.hpp"

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

	};


}