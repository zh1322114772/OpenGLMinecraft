#pragma once
#include "TickClock_Types.hpp"
#include <limits>

namespace tickerable
{
	namespace tasks
	{
		namespace outputGetterTypes
		{
			struct ChunkBuffer 
			{
				/// <summary>
				/// every unsigned long long stores 3 infomation
				///	bit 0-4: z position
				/// bit 4-8: x position
				/// bit 8-9: 0 if block is invisible, otherwise should always be 1  
				/// bit 9-32: reserved
				/// bit 32-64: texture id
				/// </summary>
				unsigned long long info[256][256] = {0};
				
				/// <summary>
				/// chunk world location
				/// </summary>
				long long locationX = LLONG_MAX, locationY = LLONG_MAX;
			};


		}


		/// <summary>
		/// this class deliver all necessary data from tick-Clock to main render thread
		/// </summary>
		class OutputGetter : public Task
		{
		private:
			/// <summary>
			/// number of active chunks
			/// </summary>
			int chunkActiveCount = 0;

			/// <summary>
			/// total chunk buffers
			/// </summary>
			outputGetterTypes::ChunkBuffer* chunkBuffers;

		public:
			/// <summary>
			/// constructor
			/// </summary>
			/// <param name="viewDistance">chunk loading radius</param>
			/// <returns></returns>
			OutputGetter(const int viewDistance);

			/// <summary>
			/// get chunk buffer size
			/// </summary>
			/// <returns></returns>
			int getChunkBufferSize();

			/// <summary>
			/// get chunk buffer
			/// </summary>
			/// <returns></returns>
			outputGetterTypes::ChunkBuffer* getChunkBuffer();

			void onEnable() override;

			void onDisable() override;

			void Tick(const double& delta_t, const std::vector<Task*>& taskList) override;

		};


	}

}