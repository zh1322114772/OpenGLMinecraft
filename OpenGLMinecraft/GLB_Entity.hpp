//define all entites in the game
#include <string>
#include <unordered_map>
#include <tuple>
#include "GLW_GlmHeaders.hpp"
#include "GLW_Types.hpp"
#include <atomic>

#include <iostream>

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



				struct RotationOffset 
				{
					glm::vec3 rotation;
					glm::vec3 offset;

					RotationOffset(glm::vec3 r, glm::vec3 o) : rotation(r), offset(o) 
					{
					
					}
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
					int meshID = -1;

					/// <summary>
					/// joint name
					/// </summary>
					std::string name;

					/// <summary>
					/// joint's children
					/// </summary>
					std::vector<Joint*> children;

					/// <summary>
					/// 
					/// </summary>
					/// <param name="ofst">joint offset at</param>
					/// <param name="rot">joint rotation direction</param>
					/// <param name="n">joint name</param>
					/// <param name="mid">corresponding mesh id</param>
					/// <returns></returns>
					Joint(glm::vec3 ofst, glm::vec3 rot, std::string n, int mid = -1) :offset(ofst), rotation(rot), name(n), meshID(mid) 
					{
					
					}

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
					const wrapperGL::VAOID* vaoID;

					/// <summary>
					/// default rotation and offset vector
					/// </summary>
					std::unordered_map<std::string, RotationOffset> rotationOffsetVectors;

					/// <summary>
					/// path of the tree to every node
					/// </summary>
					std::vector<int> path;

					/// <summary>
					/// search range of path array
					/// </summary>
					int* pathRange;

					/// <summary>
					/// size of pathRange
					/// </summary>
					int pathRangeSize;

					SharedInfo(const wrapperGL::VAOID* vid) :vaoID(vid)
					{
					
					}
				};
			}



			struct EntityRenderInfo
			{
			public:

				/// <summary>
				/// please do not create this object directly, use EntityRenderInfoMaker.makeEntityInfo()
				/// </summary>
				/// <param name="i">shared info</param>
				/// <param name="size">model matrix size</param>
				/// <param name="rProto">rotation info prototype</param>
				/// <returns></returns>
				EntityRenderInfo(entityMakerTypes::SharedInfo* i, unsigned int size, std::unordered_map<std::string, float>& rProto) : info(i), rotationRadian(rProto), modelMatrixSize(size)
				{
					modelMatrix = new glm::mat4x4[size];
				}
				
				~EntityRenderInfo() 
				{
					delete[] modelMatrix;
				}

				/// <summary>
				/// set joint rotation
				/// </summary>
				/// <param name="jointName">joint component name</param>
				/// <param name="rad">rotation in radian</param>
				void setRadian(std::string jointName, float rad);

				/// <summary>
				/// get particular joint rotation in radian
				/// </summary>
				/// <param name="jointName">joint component name</param>
				/// <returns></returns>
				float getRadian(std::string jointName);

				const glm::mat4x4* getModelMatrixArr();

				int getModelMatrixArrSize();

				const int* getPathArr();

				int getPathArrSize();

				const int* getPathIndexingArr();

				int getPathIndexingArrSize();

				int getTextureID();

				const wrapperGL::VAOID* getMeshID();
			
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

				/// <summary>
				/// model matrix size
				/// </summary>
				int modelMatrixSize;

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
				static EntityRenderInfo* getEntityInfo(EntityType which);

				static void init();

				/// <summary>
				/// get loading progress
				/// </summary>
				/// <returns></returns>
				static float getLoadingProgress();

			private:

				/// <summary>
				/// current loading progress
				/// </summary>
				static std::atomic<unsigned int> currentProgress;

				static EntityRenderInfo* protoTypeList[static_cast<unsigned int>(EntityType::LAST)];

				/// <summary>
				/// free memory
				/// </summary>
				/// <param name="modelJoint"></param>
				/// <param name="counterNode"></param>
				static void freeTree(entityMakerTypes::Joint* modelJoint, entityMakerTypes::CounterNode* counterNode);

				/// <summary>
				/// make entity prototype from Joints, 
				/// </summary>
				/// <param name="modelJoint">Joints</param>
				/// <param name="dest">where the prototype to save at</param>
				/// <param name="tid">texture id</param>
				/// <param name="vid">vao id</param>
				static EntityRenderInfo* makeRenderInfo(entityMakerTypes::Joint* modelJoint, wrapperGL::TextureID tid, const wrapperGL::VAOID* vid);

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
				static void makeRenderInfo(entityMakerTypes::CounterNode* counterNode, entityMakerTypes::Joint* modelJoint, entityMakerTypes::SharedInfo* dest, std::unordered_map<std::string, float>& rProto, std::vector<int>& step, long currentOffset);
			};



			class Entity
			{
			private:
				/// <summary>
				/// render info for entity
				/// </summary>
				EntityRenderInfo* renderableProperties;

				/// <summary>
				/// entity x y z position
				/// </summary>
				glm::vec3 entityPosition;

				/// <summary>
				/// collision check
				/// set bounding box from (0, 0, 0) - (+x, +y, +z) range
				/// </summary>
				glm::vec3 entityBoundBox;

				/// <summary>
				/// entity mass
				/// </summary>
				float mass;

			public:

				/// <summary>
				/// init entity
				/// </summary>
				/// <param name="pos">entity postion</param>
				/// <param name="boundBox">entity bounding box</param>
				/// <param name="m">entity mass</param>
				/// <param name="which">entity render info</param>
				/// <returns></returns>
				Entity(glm::vec3 pos, glm::vec3 boundBox, float m, EntityRenderInfoMaker::EntityType which);

				~Entity() 
				{
					delete renderableProperties;
				}

				/// <summary>
				/// get entity render info
				/// </summary>
				/// <returns></returns>
				EntityRenderInfo& getRenderInfo();

				/// <summary>
				/// get entity current position
				/// </summary>
				/// <returns></returns>
				glm::vec3& getPosition();

				/// <summary>
				/// get entity collision bounding box
				/// </summary>
				/// <returns></returns>
				const glm::vec3& getBoundingBox();

				/// <summary>
				/// get entity mass
				/// </summary>
				/// <returns></returns>
				const float& getMass();

			};





			class Human : public Entity 
			{
			public:
				Human(glm::vec3 pos) : Entity(pos, glm::vec3(1.0), 60, EntityRenderInfoMaker::EntityType::HUMAN) 
				{
				
				}
			};

		}

	}
}
