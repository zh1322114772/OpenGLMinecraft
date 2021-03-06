#pragma once
#include "Render_Types.hpp"
#include "GLW_Types.hpp"
#include "GLW_GLShader.hpp"
#include <memory>
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
			/// <summary>
			/// vao vertices in memory
			/// </summary>
			wrapperGL::VAOList* backgroundV;

			/// <summary>
			/// image arr in memory
			/// </summary>
			wrapperGL::ImageObject backgroundImg;

			/// <summary>
			/// vao vertices id 
			/// </summary>
			wrapperGL::VAOID backgroundVID;

			/// <summary>
			/// texture id
			/// </summary>
			wrapperGL::TextureID backgroundImgID;

			/// <summary>
			/// shader for opengl
			/// </summary>
			std::shared_ptr<wrapperGL::ShaderProgram> shader;

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