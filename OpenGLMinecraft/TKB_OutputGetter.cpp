#include "TKB_OutputGetter.hpp"
#include <math.h>
#define PI 3.1415926

namespace tickerable
{
	namespace tasks
	{
		namespace outputGetterTypes 
		{
		
		
		
		}



		OutputGetter::OutputGetter(const int viewDistance) 
		{
			chunkBuffers = new outputGetterTypes::ChunkBuffer[(int)(powf((viewDistance), 2) * PI)];
		}

		void OutputGetter::onEnable() 
		{
		
		}

		void OutputGetter::onDisable() 
		{
		
		}

		void OutputGetter::Tick(const double& delta_t, const std::vector<Task*>& taskList) 
		{
			//process chunk data

		}


	}

}