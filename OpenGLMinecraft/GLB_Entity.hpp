//define all entites in the game
#include <string>
#include <unordered_map>
#include <tuple>
#include "GLW_GlmHeaders.hpp"

namespace global
{
	namespace resource
	{
		namespace entity
		{
			namespace entityMakerTypes
			{
				struct Joint
				{
					/// <summary>
					/// the position where the current joint is connected with the parent
					/// </summary>
					glm::vec3 offset;

					/// <summary>
					/// the rotation vector of current joint
					/// </summary>
					glm::vec3 rotation;

					/// <summary>
					/// if current joint will be rendered to the screen
					/// </summary>
					bool visible;

					/// <summary>
					/// joint name
					/// </summary>
					std::string name;

					/// <summary>
					/// joint's children
					/// </summary>
					std::vector<Joint*> children;

				};
			}

			struct EntityRenderInfo
			{
				/// <summary>
				/// entity texture
				/// </summary>
				unsigned int textureID;

				/// <summary>
				/// model id
				/// </summary>
				unsigned int vaoID;

				/// <summary>
				/// model matrix for every joint
				/// </summary>
				std::unordered_map<std::string, glm::mat4x4> modelMatrix;

				/// <summary>
				/// rotation in radian
				/// </summary>
				std::unordered_map<std::string, float> rotationRadian;

			private:
				/// <summary>
				/// default rotation and offset vector
				/// </summary>
				std::unordered_map<std::string, std::tuple<glm::vec3, glm::vec3>> rotationOffsetVectors;

				/// <summary>
				/// path of the tree to every node
				/// </summary>
				int* path;

				/// <summary>
				/// size of path array
				/// </summary>
				int pathSize;

				/// <summary>
				/// search range of path array
				/// </summary>
				int* pathRange;

				/// <summary>
				/// size of pathRange
				/// </summary>
				int pathRangeSize;


			};

			class EntityRenderInfoMaker
			{
			private:


			public:

				enum class EntityType
				{
					HUMAN,




					LAST,
				};


				/// <summary>
				/// load all entity prototypes
				/// must be called in loading controller
				/// </summary>
				static void load();
				
				/// <summary>
				/// make a new entity renderable info
				/// </summary>
				/// <param name="which">entity type</param>
				/// <returns></returns>
				EntityRenderInfo* makeEntityRenderableInfo(EntityType which);

			};

			class Entity
			{
			private:
				/// <summary>
				/// render info for entity
				/// </summary>
				EntityRenderInfo renderableProperties;

				/// <summary>
				/// entity x y z position
				/// </summary>
				glm::vec3 EntityPosition;

				/// <summary>
				/// collision check
				/// set bounding box from (0, 0, 0) - (+x, +y, +z) range
				/// </summary>
				glm::vec3 EntityBoundBox;

				/// <summary>
				/// entity mass
				/// </summary>
				float mass;

			public:


			};

		}

	}
}
