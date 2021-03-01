#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

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