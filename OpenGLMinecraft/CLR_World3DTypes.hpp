#pragma once
namespace renderer
{
	namespace controllers
	{
		namespace world3DTypes
		{
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
				static const unsigned short int TYPE_BLOCK = 0b0;
				static const unsigned short int TYPE_LIQUID = 0b1;

				static const unsigned short int ATTACHMENT_INVISIBLE = 0b00;
				static const unsigned short int ATTACHMENT_VISIBLE = 0b10;
				static const unsigned short int ATTACHMENT_TRANSPARENT = 0b100;
				static const unsigned short int ATTACHMENT_RELFECT = 0b1000;

				/// <summary>
				/// texture id
				/// </summary>
				unsigned int textureID;

				/// <summary>
				/// normal map id
				/// </summary>
				unsigned int normalID;

				/// <summary>
				/// specular and occlusion map id
				/// </summary>
				unsigned int OSID;

				/// <summary>
				/// additional properties to the block
				/// </summary>
				unsigned short int properties = TYPE_BLOCK | ATTACHMENT_VISIBLE;

				/// <summary>
				/// constructor
				/// </summary>
				/// <param name="tid">texture id</param>
				/// <param name="nid">normal id</param>
				/// <param name="osid">occlusion&specular id</param>
				/// <returns></returns>
				BlockMesh(unsigned int tid, unsigned int nid, unsigned short int osid) :textureID(tid), normalID(nid), OSID(osid)
				{

				}

				/// <summary>
				/// constructor
				/// </summary>
				/// <param name="tid">texture id</param>
				/// <param name="nid">normal id</param>
				/// <param name="osid">occlusion&specular id</param>
				/// <param name="t">if texture is transparent</param>
				/// <returns></returns>
				BlockMesh(unsigned int tid, unsigned int nid, unsigned int osid, unsigned short int t) : properties(t), textureID(tid), normalID(nid), OSID(osid)
				{

				}
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


				Camera(glm::vec3 pos)
				{
					Pos = pos;
					up = glm::vec3(0.0, 1.0, 0.0);
					lookAt = glm::vec3(0.0, 0.0, 0.0);
				};

				Camera()
				{
					Pos = glm::vec3(0.0, 0.0, 0.0);
					up = glm::vec3(0.0, 1.0, 0.0);
					lookAt = glm::vec3(0.0, 0.0, 0.0);
				};

			};
		}
	}
}