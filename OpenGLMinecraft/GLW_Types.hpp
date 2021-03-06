#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GLW_GLHeaders.hpp"
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

		//element buffer object length
		int eboLength;

		//vertex buffer object length
		int vboLength;

		//vertex array
		VBO* vbos = nullptr;

		//element array
		unsigned int* ebos = nullptr;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="vboLen">vbo length</param>
		/// <param name="eboLen">ebo length</param>
		/// <returns></returns>
		VAOList(int vboLen, int eboLen);

		VAOList();

		~VAOList();

	};

	struct ImageObject 
	{
		//image byte array
		unsigned char* img_arr;

		//texture channel format
		int format;

		//image width
		int width;

		//image height
		int height;
	};


	/**
	* VAO object
	*/
	struct VAOID
	{
		//opengl vao id
		unsigned int vao_id;

		//opengl buffer id
		unsigned int vbo_id;

		//opengl buffer id
		unsigned int ebo_id;

		//element buffer object length
		int eboLength;

		//vertex buffer object length
		int vboLength;
	};

	/**
	* texture object
	*/
	struct TextureID
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



}