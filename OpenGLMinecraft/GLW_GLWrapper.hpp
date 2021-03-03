#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
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
		template<int vboSize, int eboSize>
		static VAOID loadVAOS(VAOList<eboSize, eboSize>& v);

		/// <summary>
		/// unload VAO from vram
		/// </summary>
		/// <param name="id">VAO object</param>
		static void unloadVAOS(VAOID& id);

		/// <summary>
		/// load image from disk
		/// </summary>
		/// <param name="path">image path</param>
		/// <returns></returns>
		static ImageObject loadImage(const char* path);

		/// <summary>
		/// free image object from memory
		/// </summary>
		/// <param name="obj">TextureObject</param>
		static void freeImage(ImageObject& obj);

		/// <summary>
		/// load image from disk to vram
		/// </summary>
		/// <param name="path">img directory</param>
		/// <returns>texture object</returns>
		static TextureID loadTexture(ImageObject& obj);

		/// <summary>
		/// unload texture from vram
		/// </summary>
		/// <param name="t">texture object</param>
		static void UnloadTexture(TextureID& t);



	};
}
