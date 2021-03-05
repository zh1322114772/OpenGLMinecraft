#include "GLW_Types.hpp"
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
}
