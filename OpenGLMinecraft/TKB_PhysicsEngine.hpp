#pragma once
#include "TickClock_Types.hpp"

namespace tickerable
{
	namespace tasks
	{
		class PhysicsEngine : public Task
		{
		private:

			/// <summary>
			/// detection range
			/// </summary>
			const float range;

			/// <summary>
			/// moment time
			/// </summary>
			const float deltaT;
			
		public:
			PhysicsEngine(float detectionRange, float delta);

			void onEnable() override;

			void onDisable() override;

			void onExit() override;

			void Tick(const double& delta_t, const std::vector<Task*>& taskList) override;

		};


	}
}