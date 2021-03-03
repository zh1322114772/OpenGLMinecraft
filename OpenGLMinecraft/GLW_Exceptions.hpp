#pragma once
#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace wrapperGL
{
	/// <summary>
	///GLWrapper expcetion class 
	/// </summary>
	class GlWrapperException : public std::runtime_error
	{
	public:

		explicit GlWrapperException(std::string& msg) :runtime_error(msg) 
		{
		
		}

		explicit GlWrapperException(const char* msg) :runtime_error(msg)
		{

		}

		const char* what() const override
		{
			return "GLWrapper exception";
		}

	};


}








