#include "GLSL_Code.hpp"

namespace renderer
{
	char GLSL::World3DEntityVertexShaderCode[] = 
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

		"uniform mat4 modelMat[64];\n"
		"uniform int pathArray[512];\n"
		"uniform int pathRange[64];\n"

		"uniform mat4 viewMat;\n"
		"uniform mat4 projectionMat;\n"
		"uniform vec3 location;\n"

		"void main()\n"
		"{\n"
		"vec4 worldPos = vec4(vPos, 1.0);\n"

		"int cblock = int(vBlockf);\n"
		"int begin = pathRange[(cblock * 2)];\n"
		"int end = pathRange[(cblock * 2) + 1];\n"

		"for (int i = end - 1; i >= begin; i--)\n"
		"{\n"
		"	worldPos = modelMat[pathArray[i]] * worldPos;\n"
		"}\n"
		
		"gl_Position = projectionMat * viewMat * (vec4(location, 0.0) + worldPos);\n"

		"fPos = worldPos.xyz;\n"
		"fNorm = normalize(vec4(vNorm, 1.0) * worldPos).xyz;\n"
		"fTex = vTex;\n"
		"fFace = vFace;\n"
		"}\n";

	char GLSL::World3DEntityFragmentCode[] = 
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

		"uniform sampler2D fTexture;\n"
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
		"	return texture(fTexture, org);\n"
		"};\n"

		"void main()\n"
		"{\n"
		"	vec4 textureColor = getTextureColor(fTex);\n"

		"	float fragDistance = gl_FragCoord.z;\n"
		"	vec3 globalColor = globalIllumination(globalLight, textureColor.xyz, 0.5, fNorm);\n"
		"	vec3 pointColor = pointIllumination(pointLight, textureColor.xyz, 0.5, fNorm);\n"
		"	fragColor = vec4(globalColor + pointColor, 1.0);\n"

		"};\n";

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
		"	float z = float(blockPos & 255u);\n"
		"	blockPos >>= 8;\n"

		"	float x = float(blockPos & 255u);\n"
		"	blockPos >>= 8;\n"

		"	float y = float(blockPos & 255u);\n"
		"	blockPos >>= 8;"

		"	bool invisibleFace = bool((blockPos >> int(vFace)) & 1u);\n"

		"	if(invisibleFace)\n"
		"	{\n"
		"		gl_Position = vec4(-2.0, -2.0, -2.0, 1.0);\n"
		"		return;\n"
		"	}\n"

		"	vec3 blockWorldPos = vec3(x + chunkXPosition, y, z + chunkYPosition);\n"

		"	vec4 realPos = vec4((blockWorldPos + vPos), 1.0);\n"
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
		"uniform float secondCounter;\n"
		"uniform float blockTransparent;\n"
		"uniform float blockReflect;\n"

		"out vec4 fragColor;\n"
		
		"float getCurrentFrame(int textureID, float currentY)\n"
		"{\n"
		"	ivec2 texSize = textureSize(fTexture[textureID], 0).xy;\n"
		"	float totalFrames = ceil(float(texSize.y)/ (float(texSize.x)/6));\n"
		"	return (floor(secondCounter * totalFrames) + currentY) / totalFrames;\n"
		"	"
		"}\n"

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
		"	vec2 texCoords = fTex;\n"
		"	texCoords.y = getCurrentFrame(0, texCoords.y);\n"

		"	vec4 textureColor = getTextureColor(texCoords);\n"
		"	vec2 SOColor = getSOColor(texCoords);\n"
		"	vec3 normalColor = getNormalColor(texCoords);\n"

		"	if((textureSize(fTexture[1], 0).x == 1) && (textureSize(fTexture[1], 0).y == 1))\n"
		"	{\n"
		"		normalColor = fNorm;\n"
		"	}\n"

		"	if((textureSize(fTexture[2], 0).x == 1) && (textureSize(fTexture[2], 0).y == 1))\n"
		"	{\n"
		"		SOColor.x = 0.5;\n"
		"		SOColor.y = 0.0;\n"
		"	}\n"

		"	float fragDistance = gl_FragCoord.z;\n"
		"	vec3 globalColor = globalIllumination(globalLight, textureColor.xyz, SOColor.x, normalColor);\n"
		"	vec3 pointColor = pointIllumination(pointLight, textureColor.xyz, SOColor.x, normalColor);\n"
		"	fragColor = vec4(globalColor + pointColor, blockTransparent);\n"

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