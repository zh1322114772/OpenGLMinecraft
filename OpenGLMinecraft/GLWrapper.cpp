#pragma once
#include "GLWrapper.hpp"
#include "GLWrapperExceptions.cpp"
#include "stb_image.h"

namespace wrapperGL
{
	void GLWrapper::init(GLFWwindow*& handle, const char* windowTitle, const int& height, const int& width)
	{
		//init glfw
		glfwInit();

		// set opengl version to 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//create window
		handle = glfwCreateWindow(width, height, windowTitle, NULL, NULL);

		if (handle == NULL)
		{
			throw GlWrapperException("Unable to initialize GLFW");
		}

		glfwMakeContextCurrent(handle);

		//init glad
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
		{
			throw GlWrapperException("Unable to initialize GLAD");
		}

		glViewport(0, 0, width, height);

	}

	void GLWrapper::setCursorCenter(GLFWwindow*& handle, bool b) 
	{
		if (b) 
		{
			glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		else 
		{
			glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	VAOObject GLWrapper::loadVAOS(VAOList& v)
	{
		VAOObject ret;
		
		glGenVertexArrays(1, &(ret.vao_id));

		//generate ebo and vbo buffers
		glGenBuffers(1, &(ret.ebo_id));
		glGenBuffers(1, &(ret.vbo_id));

		//bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, ret.vbo_id);
		glBufferData(GL_ARRAY_BUFFER, v.vbos.size() * sizeof(VBO), &(v.vbos[0]), GL_STATIC_DRAW);

		//bind EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ret.ebo_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, v.ebos.size() * sizeof(unsigned int), &(v.ebos[0]), GL_STATIC_DRAW);

		//bind attributes
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VBO), (void*)0); //vertex location
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VBO), (void*)offsetof(VBO, norm)); //normal direction
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VBO), (void*)offsetof(VBO, tex)); //coordinates

		//enable attributes
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);

		return ret;
	}

	void GLWrapper::unloadVAOS(VAOObject& v)
	{
		glDeleteVertexArrays(1, &(v.vao_id));
		glDeleteBuffers(1, &(v.ebo_id));
		glDeleteBuffers(1, &(v.vbo_id));
	}

	TextureObject GLWrapper::loadTexture(const char* path) 
	{
		TextureObject ret;
		int format;

		//load image to bitmap
		unsigned char* data = stbi_load(path, &(ret.width), &(ret.height), &format, 0);

		if (data) 
		{
			if (format == 3)
			{
				//rgb color format
				ret.format = GL_RGB;
			}
			else if (format == 4)
			{
				//rgba color format
				ret.format = GL_RGBA;
			}
			else 
			{
				//unsupported format
				throw GlWrapperException("Unsupported color format");
			}

			//gen texture id
			glGenTextures(1, &(ret.id));
			//bind textures
			glBindTexture(GL_TEXTURE_2D, ret.id);
			glTexImage2D(GL_TEXTURE_2D, 0, ret.format, ret.width, ret.height, 0, ret.format, GL_UNSIGNED_BYTE, data);

			//set arguments
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			//free memory
			stbi_image_free(data);

			return ret;
		}
		else 
		{
			throw GlWrapperException(("Unable to load image file: " + std::string(path)).c_str());
		}

	}

	void GLWrapper::UnloadTexture(TextureObject& t) 
	{
		glDeleteTextures(1, &(t.id));
	}


}
