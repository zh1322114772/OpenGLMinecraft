#pragma once
#include "Types.hpp"

namespace renderer 
{
	namespace controllers 
	{
		class MainGameController : public Controller 
		{
		public:

			void onStart() override;

			void onExit() override;

			void onEnable() override;

			void onDisable() override;

			void onDraw(const double& delta_t);

			void renderAreaChangedCallback(const int& newWidth, const int& newHeight);

			void inputProcess(const KeyboardEvent& keyboardEvent, const MouseEvent& mouseEvent);
		
		};
		
	}
}