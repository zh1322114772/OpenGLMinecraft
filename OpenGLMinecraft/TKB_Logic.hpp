#pragma once
#include "TickClock_Types.hpp"
namespace tickerable
{
	namespace tasks
	{
		class GameLogic : public Task 
		{
			void onEnable() override;

			void onDisable() override;

			void onExit() override;

			void Tick(const double& delta_t, const std::vector<Task*>& taskList) override;
		};


	}

}