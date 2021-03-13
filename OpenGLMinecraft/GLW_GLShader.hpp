#pragma once
#include <string>
#include "GLW_GlmHeaders.hpp"

namespace wrapperGL
{
	class ShaderProgram 
	{
	private:
		unsigned int ID;

	public:

		/// <summary>
		/// load GLSL code 
		/// </summary>
		/// <param name="vertexProgram">vertex shader code</param>
		/// <param name="fragmentProgram">fragment shader code</param>
		/// <returns></returns>
		ShaderProgram(const char* vertexCode, const char* fragmentCode);
	
		/// <summary>
		/// use this shader program
		/// </summary>
		void use();

		/// <summary>
		/// set uniform boolean to GLSL program
		/// </summary>
		/// <param name="parameter">GLSL parameter</param>
		/// <param name="val">boolean value</param>
		void setBool(const std::string& parameter, bool val) const;

		/// <summary>
		/// set uniform boolean array to GLSL program
		/// </summary>
		/// <param name="parameter">GLSL parameter</param>
		/// <param name="valArr"> boolean array</param>
		/// <param name="size"> array size</param>
		void setBool(const std::string& parameter, bool* valArr, const int size) const;

		/// <summary>
		/// set uniform integer to GLSL program
		/// </summary>
		/// <param name="parameter">GLSL parameter</param>
		/// <param name="val">integer value</param>
		void setInt(const std::string& parameter, int val) const;

		/// <summary>
		/// set uniform integer array to GLSL program
		/// </summary>
		/// <param name="parameter">GLSL parameter</param>
		/// <param name="valArr"> integer array</param>
		/// <param name="size"> array size</param>
		void setInt(const std::string& parameter, int* valArr, const int size) const;

		/// <summary>
		/// set uniform float to GLSL program
		/// </summary>
		/// <param name="parameter">GLSL parameter</param>
		/// <param name="val">float value</param>
		void setFloat(const std::string& parameter, float val) const;

		/// <summary>
		/// set uniform float array to GLSL program
		/// </summary>
		/// <param name="parameter">GLSL parameter</param>
		/// <param name="valArr"> float array</param>
		/// <param name="size"> array size</param>
		void setFloat(const std::string& parameter, float* valArr, const int size) const;

		/// <summary>
		/// set uniform vec3 to GLSL program
		/// </summary>
		/// <param name="parameter">GLSL parameter</param>
		/// <param name="val">vector3 value</param>
		void setVec3(const std::string& parameter, glm::vec3& val) const;

		/// <summary>
		/// set uniform vec4 to GLSL program
		/// </summary>
		/// <param name="parameter">GLSL parameter</param>
		/// <param name="val">vector4 value</param>
		void setVec4(const std::string& parameter, glm::vec4& val) const;

		/// <summary>
		/// set uniform matrix4*4 to GLSL program 
		/// </summary>
		/// <param name="parameter">GLSL paramete</param>
		/// <param name="val">matrix 4*4 value</param>
		void setMat4(const std::string& parameter, glm::mat4& val) const;

		~ShaderProgram();

	};

}