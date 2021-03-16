#pragma once
#include "TickClock_Types.hpp"

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
				/// bit 8-9: should be always 1,  
				/// bit 9-32: reserved
				/// bit 32-64: block id
				/// </summary>
				unsigned long long info[256][16][16] = {0};
				
				/// <summary>
				/// if chunk is ready to be rendered
				/// </summary>
				bool isVisible = false;
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
			int counter = 0;

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


			void onEnable() override;

			void onDisable() override;

			void Tick(const double& delta_t, const std::vector<Task*>& taskList) override;

		};


	}

}