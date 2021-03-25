#include "GLSL_Code.hpp"

namespace renderer
{
	char GLSL::World3DEntityVertexShaderCode[] = 
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


	char GLSL::World3DBlockVertexShaderCode[] =
		"#version 330 core\n"
		"layout(location = 0) in vec3 vPos;\n"
		"layout(location = 1) in vec3 vNorm;\n"
		"layout(location = 2) in vec2 vTex;\n"
		"layout(location = 3) in float vFace;\n"
		"layout(location = 4) in float vBlockf;\n"

		"out vec3 fPos;\n"
		"out vec3 fNorm;\n"
		"out vec2 fTex;\n"
		"out float fFace;\n"

		"uniform uint blockPosition[256];\n"
		"uniform int blockCount;\n"
		"uniform float chunkXPosition;\n"
		"uniform float chunkYPosition;\n"
		"uniform mat4 viewMat;\n"
		"uniform mat4 projectionMat;\n"

		"void main()\n"
		"{\n"
		"	int vBlock = int(vBlockf);\n"

		"	if(!(vBlock < blockCount))\n"
		"	{\n"
		"		gl_Position = vec4(-2.0, -2.0, -2.0, 1.0);\n"
		"		return;\n"
		"	}\n"

		"	uint blockPos = blockPosition[vBlock];\n"
		"	vec3 blockWorldPos = vec3(float((blockPos & 255) >> 4) + chunkXPosition, float(blockPos >> 16), float(blockPos & 15) + chunkYPosition);\n"

		"	vec4 realPos = vec4(blockWorldPos + vPos, 1.0);\n"
		"	gl_Position = projectionMat * viewMat * realPos;\n"

		"	fPos = realPos.xyz;\n"
		"	fNorm = normalize(vNorm);\n"
		"	fTex = vTex;\n"
		"	fFace = vFace;\n"
		"}\n";

	char GLSL::World3DBlockFragmentCode[] =
		"#version 330 core\n"

		"in vec3 fPos;\n"
		"in vec3 fNorm;\n"
		"in vec2 fTex;\n"
		"in float fFace;\n"

		"struct GlobalLight\n"
		"{\n"
		"	vec3 lightDirection;\n"
		"	vec3 lightColorA;\n"
		"	vec3 lightColorD;\n"
		"	vec3 lightColorS;\n"
		"};\n"

		"struct PointLight\n"
		"{\n"
		"	vec3 lightPosition;\n"
		"	vec3 lightColorD;\n"
		"	vec3 lightColorS;\n"
		"};\n"

		"uniform sampler2D fTexture[3];\n"
		"uniform GlobalLight globalLight;\n"
		"uniform PointLight pointLight;\n"
		"uniform vec3 cameraPosition;\n"

		"out vec4 fragColor;\n"
		
		"vec3 pointIllumination(PointLight l, vec3 color, float specular, vec3 normPos)\n"
		"{\n"

		"	vec3 lightDirection = normalize(fPos - l.lightPosition);\n"
		"	float distance = length(fPos - l.lightPosition);\n"
		"	float attenuation = 1.0/(1.0 + (0.027 * distance) + (0.0028 * pow(distance, 2)));\n"

		"	float directBrightness = max(0, dot(-lightDirection, normPos));\n"
		"	vec3 directColor = color * directBrightness * l.lightColorD;\n"

		"	vec3 lightReflection = reflect(lightDirection, normPos);\n"
		"	vec3 cameraDirection = normalize(cameraPosition - fPos);\n"
		"	float specularBrightness = pow(max(0, dot(lightReflection, cameraDirection)), 16) * specular;\n"
		"	vec3 specularColor = color * specularBrightness * l.lightColorS;\n"

		"	return (directColor + specularColor) * attenuation;\n"
		"}\n"

		"vec3 globalIllumination(GlobalLight l, vec3 color, float specular, vec3 normPos)\n"
		"{\n"
		"	vec3 ambientColor = color * l.lightColorA;\n"

		"	float directBrightness = max(0, dot(-l.lightDirection, normPos));\n"
		"	vec3 directColor = color * directBrightness * l.lightColorD;\n"
	
		"	vec3 lightReflection = reflect(l.lightDirection, normPos);\n"
		"	vec3 cameraDirection = normalize(cameraPosition - fPos);\n"
		"	float specularBrightness = pow(max(0, dot(lightReflection, cameraDirection)), 32) * specular;\n"
		"	vec3 specularColor = color * specularBrightness * l.lightColorS;\n"

		"	return ambientColor + directColor + specularColor;\n"
		"};\n"

		"vec4 getTextureColor(vec2 org)\n"
		"{\n"
		"	float x = ((fFace + org.x)/ 6.0);\n"
		"	float y = org.y;\n"
		"	return texture(fTexture[0], vec2(x, y));\n"
		"};\n"

		"vec3 getNormalColor(vec2 org)\n"
		"{\n"
		"	float x = ((fFace + org.x)/ 6.0);\n"
		"	float y = org.y;\n"
		"	vec3 normal = (texture(fTexture[1], vec2(x, y)).xyz * 2.0) - 1.0;\n"
		"	normal.y = -normal.y;\n"
		"	return normalize(normal);\n"
		"};\n"

		"vec2 getSOColor(vec2 org)\n"
		"{\n"
		"	int offset = int(fFace) / 2;\n"
		"	int select = int(fFace) % 2;\n"

		"	float x = (float(offset) + org.x)/ 3;\n"
		"	float y = org.y;\n"
		"	vec4 res = texture(fTexture[2], vec2(x, y));\n"
		"	return vec2(res[select * 2], res[(select * 2) + 1]);\n"
		"}\n"

		"void main()\n"
		"{\n"

		"	vec4 textureColor = getTextureColor(fTex);\n"
		"	vec2 SOColor = getSOColor(fTex);\n"
		"	vec3 normalColor = getNormalColor(fTex);\n"

		"	vec3 globalColor = globalIllumination(globalLight, textureColor.xyz, SOColor.x, normalColor);\n"
		"	vec3 pointColor = pointIllumination(pointLight, textureColor.xyz, SOColor.x, normalColor);\n"
		"	fragColor = vec4(pointColor + globalColor, 1.0);\n"

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