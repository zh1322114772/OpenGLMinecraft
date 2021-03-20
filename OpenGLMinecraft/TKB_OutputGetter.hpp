#pragma once
#include "TickClock_Types.hpp"
#include "TKB_ChunkLoader.hpp"
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

				/// <summary>
				/// chunk time stamp
				/// </summary>
				long long timeStamp = 0;

				unsigned int chunkID;
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
			outputGetterTypes::ChunkBuffer** chunkBuffers;

			/// <summary>
			/// chunk buffer active list
			/// </summary>
			outputGetterTypes::ChunkBuffer** chunkBuffersActive;



			/// <summary>
			/// chunk render buffer size
			/// </summary>
			int chunkBufferSize;

			/// <summary>
			/// process chunk data to chunk buffer
			/// </summary>
			/// <param name="chunkBuffer">chunk buffer</param>
			/// <param name="chunkData">chunk data</param>
			void chunkData2ChunkBuffer(outputGetterTypes::ChunkBuffer* chunkBuffer, tasks::chunkLoaderTypes::Chunk* chunkData);

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
			outputGetterTypes::ChunkBuffer** getChunkBuffers();

			void onEnable() override;

			void onDisable() override;

			void onExit() override;

			void Tick(const double& delta_t, const std::vector<Task*>& taskList) override;

		};


	}

}