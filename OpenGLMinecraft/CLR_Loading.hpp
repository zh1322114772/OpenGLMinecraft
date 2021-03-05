#pragma once
#include "Render_Types.hpp"
#include "GLW_Types.hpp"

/// <summary>
/// this controller load resources from disk
/// </summary>
namespace renderer
{

	namespace controllers
	{
		class Loading : public Controller 
		{
		private:
			wrapperGL::VAOList background;

		public:

			Loading();

			void onStart() override;

			void onExit() override;

			void onEnable() override;

			void onDisable() override;

			void onDraw(const double& delta_t) override;

			void renderAreaChangedCallback(const int& newWidth, const int& newHeight);

			void inputProcess(const KeyboardEvent& keyboardEvent, const MouseEvent& mouseEvent, const double& delta_t);
		
		
		};

	}

}