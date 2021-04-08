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
				struct CounterNode 
				{
					unsigned int modelMatrixCount = 0;
					unsigned int meshCount = 0;
					std::vector<CounterNode*> children;
				};

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
					/// corresponding mesh id
					/// </summary>
					unsigned int meshID = -1;

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

				struct SharedInfo 
				{
					/// <summary>
					/// indexing every model matrix
					/// </summary>
					std::unordered_map<std::string, long> modelMatrixIndexing;

					/// <summary>
					/// entity texture
					/// </summary>
					unsigned int textureID;

					/// <summary>
					/// model id
					/// </summary>
					unsigned int vaoID;

					/// <summary>
					/// default rotation and offset vector
					/// </summary>
					std::unordered_map<std::string, std::tuple<glm::vec3, glm::vec3>>* rotationOffsetVectors;

					/// <summary>
					/// path of the tree to every node
					/// </summary>
					std::vector<unsigned int> path;

					/// <summary>
					/// search range of path array
					/// </summary>
					int* pathRange;

					/// <summary>
					/// size of pathRange
					/// </summary>
					int pathRangeSize;
				};
			}

			struct EntityRenderInfo
			{
			public:

				/// <summary>
				/// please do not create this object directly, use EntityRenderInfoMaker.makeEntityInfo()
				/// </summary>
				/// <param name="i">shared info</param>
				/// <param name="modelMatrixSize">model matrix size</param>
				/// <param name="rProto">rotation info prototype</param>
				/// <returns></returns>
				EntityRenderInfo(entityMakerTypes::SharedInfo* i, unsigned int modelMatrixSize, std::unordered_map<std::string, float>& rProto) : info(i), rotationRadian(rProto)
				{
					modelMatrix = new glm::mat4x4[modelMatrixSize];
				}
				
				/// <summary>
				/// please do not create this object directly, use EntityRenderInfoMaker.makeEntityInfo()
				/// </summary>
				EntityRenderInfo() {}
			
			private:
				/// <summary>
				/// shared render info of all instances
				/// </summary>
				entityMakerTypes::SharedInfo* info = nullptr;

				/// <summary>
				/// rotation in radian
				/// </summary>
				std::unordered_map<std::string, float> rotationRadian;

				/// <summary>
				/// model matrix for every joint
				/// </summary>
				glm::mat4x4* modelMatrix = nullptr;

			};

			class EntityRenderInfoMaker
			{
			
			public:

				enum class EntityType
				{
					CUBE,
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
				static EntityRenderInfo* makeEntityInfo(EntityType which);

			private:

				static EntityRenderInfo protoTypeList[static_cast<unsigned int>(EntityType::LAST)];

				/// <summary>
				/// make entity prototype from Joints, 
				/// </summary>
				/// <param name="modelJoint">Joints</param>
				/// <param name="dest">where the prototype to save at</param>
				static void makeRenderInfo(entityMakerTypes::Joint* modelJoint, EntityRenderInfo& dest);

				/// <summary>
				/// make a counter tree that counts the size of children tree nodes
				/// </summary>
				/// <param name=""></param>
				/// <returns></returns>
				static entityMakerTypes::CounterNode* makeCounterTree(entityMakerTypes::Joint*);

				/// <summary>
				///  make entity prototype from Joints
				/// </summary>
				/// <param name="counterNode">counter tree</param>
				/// <param name="modelJoint">joints</param>
				/// <param name="dest">shared info</param>
				/// <param name="rProto">rotation info</param>
				/// <param name="step">path from root to node</param>
				static void makeRenderInfo(entityMakerTypes::CounterNode* counterNode, entityMakerTypes::Joint* modelJoint, entityMakerTypes::SharedInfo* dest, std::unordered_map<std::string, float>& rProto, std::vector<unsigned int>& step, long currentOffset);
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
