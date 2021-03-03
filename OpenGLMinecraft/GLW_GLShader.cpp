#include "GLW_GLShader.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "GLW_Exceptions.hpp"
#define paraLoc glGetUniformLocation(ID, parameter.c_str())

namespace wrapperGL
{
	

	ShaderProgram::ShaderProgram(const char* vertexCode, const char* fragmentCode)
	{
		unsigned int vertexID, fragmentID;
		int success;
		char infoLog[512];

		//compile shader program
		vertexID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexID, 1, &vertexCode, NULL);
		glCompileShader(vertexID);

		//check if successfully compiled
		glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
		if (!success) 
		{
			glGetShaderInfoLog(vertexID, 512, NULL, infoLog);
			throw GlWrapperException(infoLog);
		}

		//compile fragment program
		fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentID, 1, &fragmentCode, NULL);
		glCompileShader(fragmentID);

		//check if successfully compiled
		glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
		if(!success)
		{
			glGetShaderInfoLog(fragmentID, 512, NULL, infoLog);
			throw GlWrapperException(infoLog);
		}

		//link to program
		ID = glCreateProgram();
		glAttachShader(ID, vertexID);
		glAttachShader(ID, fragmentID);
		glLinkProgram(ID);

		//check link status
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) 
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			throw GlWrapperException(infoLog);
		}

		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
	}

	void ShaderProgram::use() 
	{
		glUseProgram(ID);
	}

	void ShaderProgram::setBool(const std::string& parameter, bool val) const 
	{
		glUniform1i(paraLoc, val);
	};

	void ShaderProgram::setInt(const std::string& parameter, int val) const 
	{
		glUniform1i(paraLoc, val);
	};

	void ShaderProgram::setFloat(const std::string& parameter, float val) const 
	{
		glUniform1f(paraLoc, val);
	};

	void ShaderProgram::setVec3(const std::string& parameter, glm::vec3& val) const 
	{
		glUniform3fv(paraLoc, 1, glm::value_ptr(val));
	};

	void ShaderProgram::setVec4(const std::string& parameter, glm::vec4& val) const 
	{
		glUniform4fv(paraLoc, 1, glm::value_ptr(val));
	};

	void ShaderProgram::setMat4(const std::string& parameter, glm::mat4& val) const 
	{
		glUniformMatrix4fv(paraLoc, 1, GL_FALSE, glm::value_ptr(val));
	};

	ShaderProgram::~ShaderProgram() 
	{
		glDeleteProgram(ID);
	}

}