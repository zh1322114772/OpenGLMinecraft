#pragma once
#include "GLW_GlmHeaders.hpp"
#include "GLW_Types.hpp"
#include <vector>
namespace renderer
{
	namespace controllers
	{
		namespace world3D 
		{
			/// <summary>
			/// included four 
			/// </summary>
			struct TextureBundle 
			{
				/// <summary>
				/// texture
				/// </summary>
				unsigned int texture;

				/// <summary>
				/// occlusion & specular map , where red the channel is occlusion bit map and green channel is specular map
				/// </summary>
				unsigned int textureOS;

				/// <summary>
				/// normal map
				/// </summary>
				unsigned int textureN;

				/// <summary>
				/// image height
				/// </summary>
				unsigned short int height;

				/// <summary>
				/// image width
				/// </summary>
				unsigned short int width;

				/// <summary>
				/// if texture has animation
				/// </summary>
				bool hasAnimation;

				/// <summary>
				/// the next animation frame
				/// </summary>
				unsigned short int currentFrame;

				/// <summary>
				/// height for single animation frame
				/// </summary>
				unsigned short int singleFrameHeight;

				/// <summary>
				/// total animation frames
				/// </summary>
				unsigned short int maxFrame;

				/// <summary>
				/// constructor
				/// </summary>
				/// <param name="tex">texture bit map</param>
				/// <param name="texS">specular bit map</param>
				/// <param name="texO">occlusion bit map</param>
				/// <param name="texN"></param>
				/// <returns></returns>
				TextureBundle(const wrapperGL::TextureID& tex, const wrapperGL::TextureID& texOS, const wrapperGL::TextureID& texN);

				/// <summary>
				/// constructor
				/// </summary>
				/// <param name="tex">texture bit map</param>
				/// <returns></returns>
				TextureBundle(const wrapperGL::TextureID& tex);

				/// <summary>
				/// set texture to animation type
				/// </summary>
				/// <param name="frameHeight">single frame height</param>
				void setAnimation(unsigned short int frameHeight);

			};

			/// <summary>
			/// 3d Polygon object
			/// </summary>
			struct Mesh 
			{
				
			};

			/// <summary>
			/// 3d block object
			/// </summary>
			struct BlockMesh 
			{
				/// <summary>
				/// vao id
				/// </summary>
				unsigned int VAOID;

				/// <summary>
				/// the face that's pointing at (0, 0, 1) direction
				/// </summary>
				TextureBundle faceA;

				/// <summary>
				/// the face that's pointing at (-1, 0, 0) direction
				/// </summary>
				TextureBundle faceB;

				/// <summary>
				/// the face that's pointing at (0, 0, -1) direction
				/// </summary>
				TextureBundle faceC;

				/// <summary>
				/// the face that's pointing at (1, 0, 0) direction
				/// </summary>
				TextureBundle faceD;

				/// <summary>
				/// the face that's pointing at (0, 1, 0) direction
				/// </summary>
				TextureBundle faceE;

				/// <summary>
				/// the face that's pointing at (0, -1, 0) direction
				/// </summary>
				TextureBundle faceF;

				/// <summary>
				///	constructor
				/// </summary>
				/// <param name="fa">face a</param>
				/// <param name="fb">face b</param>
				/// <param name="fc">face c</param>
				/// <param name="fd">face d</param>
				/// <param name="fe">face e</param>
				/// <param name="ff">face f</param>
				/// <param name="vao">vao list</param>
				/// <returns></returns>
				BlockMesh(TextureBundle& fa, TextureBundle& fb, TextureBundle& fc, TextureBundle& fd, TextureBundle& fe, TextureBundle& ff, wrapperGL::VAOID& vao);

				/// <summary>
				/// constructor
				/// </summary>
				/// <param name="fa">face</param>
				/// <param name="vao">vao list</param>
				/// <returns></returns>
				BlockMesh(TextureBundle& fa, wrapperGL::VAOID& vao);
			};

			struct Camera 
			{
				/// <summary>
				/// camera up vector
				/// </summary>
				glm::vec3 up;

				/// <summary>
				/// camera world position
				/// </summary>
				glm::vec3 Pos;

				/// <summary>
				/// camera direction
				/// </summary>
				glm::vec3 lookAt;


				Camera(glm::vec3 pos);

				Camera();

			};
		
		}
	}
}
