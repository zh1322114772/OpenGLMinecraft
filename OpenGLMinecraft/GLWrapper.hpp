#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>


namespace wrapperGL
{
	/**
	* VBO object
	*/
	struct VBO
	{
		//position
		glm::vec3 pos;

		//normal vecor
		glm::vec3 norm;

		//texture coordinates
		glm::vec2 tex;
	};

	/**
	* contains list of EBO, VBO 
	*/
	struct VAOList
	{
		std::vector<VBO> vbos;
		std::vector<unsigned int>ebos;
	};

	/**
	* VAO object
	*/
	struct VAOObject
	{
		//opengl vao id
		unsigned int vao_id;

		//opengl buffer id
		unsigned int vbo_id;

		//opengl buffer id
		unsigned int ebo_id;
	};

	/**
	* texture object
	*/
	struct TextureObject
	{
		//texture id
		unsigned int id;

		//texture format either GL_RGB or GL_RGBA
		GLenum format;

		//image width
		int width;
	
		//image height
		int height;
	};

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
		static VAOObject loadVAOS(VAOList& v);

		/// <summary>
		/// unload VAO from vram
		/// </summary>
		/// <param name="id">VAO object</param>
		static void unloadVAOS(VAOObject& id);

		/// <summary>
		/// load image from disk to vram
		/// </summary>
		/// <param name="path">img directory</param>
		/// <returns>texture object</returns>
		static TextureObject loadTexture(const char* path);

		/// <summary>
		/// unload texture from vram
		/// </summary>
		/// <param name="t">texture object</param>
		static void UnloadTexture(TextureObject& t);



	};
}
