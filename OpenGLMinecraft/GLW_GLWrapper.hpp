#pragma once
#include "GLW_GLHeaders.hpp"
#include "GLW_GLShader.hpp"
#include "GLW_GlmHeaders.hpp"
#include <vector>
#include "GLW_Types.hpp"


namespace wrapperGL
{
	/**
	* wrap some opengl functions
	*/
	class GLWrapper
	{
	public:

		/// <summary>
		/// initialize glfw and glad
		/// </summary>
		/// <param name="handle">glfw window handle</param>
		/// <param name="windowTitle">window title</param>
		/// <param name="height">window height</param>
		/// <param name="width">window width</param>
		static void init(GLFWwindow*& handle, const char* windowTitle, const int& height, const int& width);

		/// <summary>
		/// let mouse stays center
		/// </summary>
		/// <param name="handle">window handle</param>
		/// <param name="b"></param>
		static void setCursorCenter(GLFWwindow*& handle ,bool b);

		/// <summary>
		/// load VAO list to vram
		/// </summary>
		/// <param name="v">vao list object</param>
		/// <returns>vao object</returns>
		static VAOID loadVAOS(VAOList* v);

		/// <summary>
		/// unload VAO from vram
		/// </summary>
		/// <param name="id">VAO object</param>
		static void unloadVAOS(const VAOID& id);

		/// <summary>
		/// load image from disk
		/// </summary>
		/// <param name="path">image path</param>
		/// <returns></returns>
		static ImageObject* loadImage(const char* path);

		/// <summary>
		/// free image object from memory
		/// </summary>
		/// <param name="obj">TextureObject</param>
		static void freeImage(ImageObject* obj);

		/// <summary>
		/// free image char arr from memory
		/// </summary>
		/// <param name="p"></param>
		static void freeImage(void* p);

		/// <summary>
		/// load image from disk to vram
		/// </summary>
		/// <param name="path">img directory</param>
		/// <returns>texture object</returns>
		static TextureID loadTexture(ImageObject* obj);

		/// <summary>
		/// to bind a texture to simpler2D
		/// </summary>
		/// <param name="shader">current shader program</param>
		/// <param name="tid">TextureID object</param>
		/// <param name="parameter">GLSL simpler2D name</param>
		/// <param name="texture_id">bind to texture id</param>
		static void activateTexture(ShaderProgram* shader ,const TextureID& tid, const char* parameter, int texture_id);

		/// <summary>
		/// wrapper for glDrawElement
		/// </summary>
		/// <param name="vid">VAOID</param>
		static void draw(const VAOID& vid);

		/// <summary>
		/// unload texture from vram
		/// </summary>
		/// <param name="t">texture object</param>
		static void UnloadTexture(TextureID& t);



	};
}
