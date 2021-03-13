#include "GLSL_Code.hpp"

namespace renderer
{
	char GLSL::World3DvertexShaderCode[] =
		"#version 330 core\n"
		"layout(location = 0) in vec3 vPos;\n"
		"layout(location = 1) in vec3 vNorm;\n"
		"layout(location = 2) in vec2 vTex;\n"
		"layout(location = 3) in float vFace;\n"

		"out vec3 fPos;\n"
		"out vec3 fNorm;\n"
		"out vec2 fTex;\n"
		"out float fFace;\n"

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
		"fFace = vFace;\n"
		"}\n";

	char GLSL::World3DWorldFragmentCode[] =
		"#version 330 core\n"

		"in vec3 fPos;\n"
		"in vec3 fNorm;\n"
		"in vec2 fTex;\n"
		"in float fFace;\n"

		"uniform sampler2D fTexture;\n"

		"out vec4 fragColor;\n"

		"vec2 getTextureCoords(vec2 org, float face)\n"
		"{\n"
		"	float x = ((face + org.x)/ 15.0);\n"
		"	float y = org.y;\n"
		"	return vec2(x, y);\n"
		"};\n"

		"void main()\n"
		"{\n"
		"	fragColor = vec4(texture(fTexture, getTextureCoords(fTex, fFace)).xyz, 1.0);\n"
		"};\n";

	char GLSL::LoadingShaderCode[] =
		"#version 330 core\n"
		"layout(location = 0) in vec3 vPos;\n"
		"layout(location = 1) in vec3 vNorm;\n"
		"layout(location = 2) in vec2 vTex;\n"
		"layout(location = 3) in float vFace;\n"

		"out vec2 fTex;\n"

		"void main()\n"
		"{\n"
		"	gl_Position = vec4(vPos, 1.0);\n"
		"	fTex = vTex;\n"
		"}\n";

	char GLSL::LoadingFragmentCode[] =
		"#version 330 core\n"

		"uniform sampler2D fTexture;\n"
		"uniform float progress;\n"
		"in vec2 fTex;\n"

		"out vec4 fragColor;\n"

		"void main()\n"
		"{\n"
		"	if(fTex.y > 0.95 && fTex.x < progress)\n"
		"	{\n"
		"		fragColor = vec4(0.0, 0.635, 0.909, 1.0);\n"
		"	}else{\n"
		"		fragColor = vec4(texture(fTexture, fTex).xyz, 1.0);\n"
		"	}\n"
		"}\n";

}