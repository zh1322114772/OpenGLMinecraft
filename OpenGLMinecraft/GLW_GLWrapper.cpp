#include "GLW_GLWrapper.hpp"
#include <stb_image.h>
#include <iostream>
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
			throw std::runtime_error("Unable to initialize GLFW");
		}

		glfwMakeContextCurrent(handle);

		//init glad
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
		{
			throw std::runtime_error("Unable to initialize GLAD");
		}

		glViewport(0, 0, width, height);
		stbi_set_flip_vertically_on_load(true);
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

	VAOID GLWrapper::loadVAOS(VAOList& v)
	{
		VAOID ret;
		
		glGenVertexArrays(1, &(ret.vao_id));

		//generate ebo and vbo buffers
		glGenBuffers(1, &(ret.ebo_id));
		glGenBuffers(1, &(ret.vbo_id));

		//bind VAO
		glBindVertexArray(ret.vao_id);

		//bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, ret.vbo_id);
		glBufferData(GL_ARRAY_BUFFER, v.vboLength * sizeof(VBO), v.vbos, GL_STATIC_DRAW);

		//bind EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ret.ebo_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, v.eboLength * sizeof(unsigned int), v.ebos, GL_STATIC_DRAW);

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

	void GLWrapper::unloadVAOS(VAOID& v)
	{
		glDeleteVertexArrays(1, &(v.vao_id));
		glDeleteBuffers(1, &(v.ebo_id));
		glDeleteBuffers(1, &(v.vbo_id));
	}

	ImageObject GLWrapper::loadImage(const char* path) 
	{
		ImageObject ret;
		ret.img_arr = stbi_load(path, &(ret.width), &(ret.height), &(ret.format), 0);

		if (!ret.img_arr) throw std::runtime_error(("Unable to load image file: " + std::string(path)).c_str());

		return ret;
	}

	void GLWrapper::freeImage(ImageObject& obj) 
	{
		stbi_image_free(obj.img_arr);
	}

	TextureID GLWrapper::loadTexture(ImageObject& obj)
	{
		TextureID ret;

		if (obj.format == 3)
		{
			//rgb color format
			ret.format = GL_RGB;
		}
		else if (obj.format == 4)
		{
			//rgba color format
			ret.format = GL_RGBA;
		}
		else 
		{
			//unsupported format
			throw std::runtime_error("Unsupported color format");
		}

		ret.height = obj.height;
		ret.width = obj.width;

		//gen texture id
		glGenTextures(1, &(ret.id));
		//bind textures
		glBindTexture(GL_TEXTURE_2D, ret.id);

		//set arguments
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, ret.format, ret.width, ret.height, 0, ret.format, GL_UNSIGNED_BYTE, obj.img_arr);
		glGenerateMipmap(GL_TEXTURE_2D);

		return ret;
	}

	void GLWrapper::UnloadTexture(TextureID& t) 
	{
		glDeleteTextures(1, &(t.id));
	}
	
	void GLWrapper::activeTexture(ShaderProgram* shader, TextureID& tid, const char* parameter, int texture_id)
	{
		shader->setInt(parameter, texture_id - GL_TEXTURE0);
		glActiveTexture(texture_id);
		glBindTexture(GL_TEXTURE_2D, tid.id);
	
	}


}
