#include "GLW_Types.hpp"
#include "GLW_GLWrapper.hpp"
#include <iostream>
namespace wrapperGL
{
	VAOList::VAOList(int vboLen, int eboLen)
	{
		eboLength = eboLen;
		vboLength = vboLen;

		ebos = new unsigned int[eboLength];
		vbos = new VBO[vboLength];
	}

	VAOList::VAOList() 
	{
		eboLength = -1;
		vboLength = -1;
	}

	VAOList::~VAOList()
	{
		delete[] vbos;
		delete[] ebos;
	}

	ImageObject::ImageObject() 
	{
		img_arr = nullptr;
		format = -1;
		height = -1;
		width = -1;
	}

	ImageObject::~ImageObject() 
	{
		wrapperGL::GLWrapper::freeImage(img_arr);
	}

	VBO::VBO() 
	{
		pos = glm::vec3(0.0);
		norm = glm::vec3(0.0);
		tex = glm::vec2(0.0);
		face = 0.0;
		extra = 0.0;
	}

	VAOID::VAOID() 
	{
		vao_id = -1;
		vbo_id = -1;
		ebo_id = -1;
		eboLength = -1;
		vboLength = -1;
	}

	TextureID::TextureID() 
	{
		id = -1;
		format = -1;
		width = -1;
		height = -1;

	}

}
