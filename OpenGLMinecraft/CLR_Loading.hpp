#pragma once
#include "Render_Types.hpp"
#include "GLW_Types.hpp"
#include "GLW_GLShader.hpp"
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
			wrapperGL::ImageObject* backgroundImg;

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
			wrapperGL::ShaderProgram* shader;

			/// <summary>
			/// current total loading progress
			/// </summary>
			float progress;

			/// <summary>
			/// current texture loading progress adjusted 0-1
			/// </summary>
			float textureLoaderProgress;

			/// <summary>
			/// current texture loading progress unadjusted
			/// </summary>
			int textureLoaderProgressI;

			/// <summary>
			/// load textures to vram
			/// </summary>
			inline void textureLoader();

			/// <summary>
			/// current meshblock loading progress adjusted to 0-1
			/// </summary>
			float meshBlockLoaderProgress;

			/// <summary>
			/// load meshblocks
			/// </summary>
			inline void meshBlockLoader();

			/// <summary>
			/// current vertices loading progress adjusted to 0-1
			/// </summary>
			float verticesLoaderProgress;

			/// <summary>
			/// load vertices
			/// </summary>
			inline void verticesLoader();

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