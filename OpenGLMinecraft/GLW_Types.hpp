#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <initializer_list>
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

	template<int vboSize, int eboSize>
	struct VAOList
	{
		VBO vbos[vboSize];
		unsigned int ebos[eboSize];

		const int vboLength = vboSize;
		const int eboLength = eboSize;

		void setVbos(std::initializer_list<float> l)
		{
			if ((l.size() / 8) == vboLength) 
			{
				memcpy(&vbos, l.begin(), l.size()*sizeof(float));
			}
		}

		void setEbos(std::initializer_list<unsigned int> l) 
		{
			if (l.size() == eboLength) 
			{
				memcpy(&ebos, l.begin(), l.size() * sizeof(unsigned int));
			}
		}
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