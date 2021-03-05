#include "GLSL_Code.hpp"

namespace renderer
{
	char GLSL::World3DvertexShaderCode[] =
		"#version 330 core\n"
		"layout(location = 0) in vec3 vPos;\n"
		"layout(location = 1) in vec3 vNorm;\n"
		"layout(location = 2) in vec2 vTex;\n"

		"out vec3 fPos;\n"
		"out vec3 fNorm;\n"
		"out vec2 fTex;\n"

		"uniform mat4 modelMat[48];\n"
		"uniform int modelMatSize;\n"
		"uniform mat4 viewMat;\n"
		"uniform mat4 projectionMat;\n"

		"void main()\n"
		"{\n"
		"vec4 worldPos = vec4(vPos, 1.0);\n"
		"for (int i = 0; i < modelMatSize; i++)\n"
		"{\n"
		"worldPos = modelMat[i] * worldPos;\n"
		"}\n"
		"gl_Position = projectionMat * viewMat * worldPos;\n"

		"fPos = worldPos.xyz;\n"
		"fNorm = normalize(vNorm);\n"
		"fTex = vTex;\n"
		"}\n";

	char GLSL::World3DFragmentCode[] =
		"#version 330 core\n"

		"uniform sampler2D fTexture;\n"
		"in vec3 fPos;\n"
		"in vec3 fNorm;\n"
		"in vec2 fTex;\n"

		"out vec4 fragColor;\n"

		"void main()\n"
		"{\n"
		"	fragColor = vec4(texture(fTexture, fTex).xyz, 1.0);\n"
		"}\n";

	char GLSL::LoadingShaderCode[] =
		"#version 330 core\n"

		"layout(location = 0) in vec3 vPos;\n"
		"layout(location = 1) in vec3 vNorm;\n"
		"layout(location = 2) in vec2 vTex;\n"

		"out vec2 fTex;\n"

		"void main()\n"
		"{\n"
		"gl_Position = vec4(vPos, 1.0);\n"
		"fTex = vTex;\n"
		"}\n";

	char GLSL::LoadingFragmentCode[] =
		"#version 330 core\n"

		"uniform sampler2D fTexture;\n"
		"in vec2 fTex;\n"

		"out vec4 fragColor;\n"

		"void main()\n"
		"{\n"
		"	fragColor = vec4(texture(fTexture, fTex).xyz, 1.0);\n"
		"}\n";

}