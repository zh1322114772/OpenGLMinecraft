#include "CLR_World3D_Types.hpp"
#include "GLW_GlmHeaders.hpp"
#include <stdexcept>

namespace renderer
{
	namespace controllers
	{
		namespace world3D
		{
			Camera::Camera(glm::vec3 pos)
			{
				Pos = pos;
				up = glm::vec3(0.0, 1.0, 0.0);
				lookAt = glm::vec3(0.0, 0.0, 0.0);
			}

			Camera::Camera()
			{
				Pos = glm::vec3(0.0, 0.0, 0.0);
				up = glm::vec3(0.0, 1.0, 0.0);
				lookAt = glm::vec3(0.0, 0.0, 0.0);
			}
			
			TextureBundle::TextureBundle(const wrapperGL::TextureID& tex, const wrapperGL::TextureID& texOS, const wrapperGL::TextureID& texN)
			{
				texture = tex.id;
				textureOS = texOS.id;
				textureN = texN.id;

				height = (unsigned short int)tex.height;
				width = (unsigned short int)tex.width;

				hasAnimation = false;
				currentFrame = -1;
				maxFrame = -1;
				singleFrameHeight = -1;
			}

			TextureBundle::TextureBundle(const wrapperGL::TextureID& tex) 
			{
				textureOS = -1;
				textureN = -1;
				texture = tex.id;

				height = (unsigned short int)tex.height;
				width = (unsigned short int)tex.width;

				hasAnimation = false;
				currentFrame = -1;
				maxFrame = -1;
				singleFrameHeight = -1;
			}

			void TextureBundle::setAnimation(unsigned short int frameHeight) 
			{
				if (frameHeight >= height) 
				{
					throw std::runtime_error("single frame height cannot be larger than total texture height");
				}

				hasAnimation = true;
				currentFrame = 0;
				maxFrame = height / frameHeight;
				singleFrameHeight = frameHeight;
			}

			BlockMesh::BlockMesh(TextureBundle& fa, TextureBundle& fb, TextureBundle& fc, TextureBundle& fd, TextureBundle& fe, TextureBundle& ff, wrapperGL::VAOID& vao):faceA(fa), faceB(fb), faceC(fc), faceD(fd), faceE(fe), faceF(ff), VAOID(vao)
			{

			}

			BlockMesh::BlockMesh(TextureBundle& f, wrapperGL::VAOID& vao) : faceA(f), faceB(f), faceC(f), faceD(f), faceE(f), faceF(f), VAOID(vao)
			{

			}
		}
	}

}
