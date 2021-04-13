#include "GLB_Entity.hpp"
#include "GLB_Texture.hpp"
#include "GLB_Mesh.hpp"
#include <stdexcept>

namespace global
{
	namespace resource
	{
		namespace entity
		{
			EntityRenderInfo* EntityRenderInfoMaker::protoTypeList[static_cast<unsigned int>(EntityType::LAST)];
			std::atomic<unsigned int> EntityRenderInfoMaker::currentProgress;

			Entity::Entity(glm::vec3 pos, glm::vec3 boundBox, float m, EntityRenderInfoMaker::EntityType which): entityPosition(pos), entityBoundBox(boundBox), mass(m)
			{
				renderableProperties = EntityRenderInfoMaker::getEntityInfo(which);
			}

			EntityRenderInfo& Entity::getRenderInfo() 
			{
				return *renderableProperties;
			}

			glm::vec3& Entity::getPosition() 
			{
				return entityPosition;
			}

			const glm::vec3& Entity::getBoundingBox() 
			{
				return entityBoundBox;
			}

			const float& Entity::getMass() 
			{
				return mass;
			}








			void EntityRenderInfo::setRadian(std::string jointName, float rad) 
			{

				auto got = rotationRadian.find(jointName);
				auto gotModelIndex = info->modelMatrixIndexing.find(jointName);
				auto gotVecs = info->rotationOffsetVectors.find(jointName);

				if (got == rotationRadian.end()) 
				{
					throw std::runtime_error("unable to find the joint name: " + jointName);
				}

				got->second = rad;
				auto temp = glm::translate(glm::mat4(1.0f), gotVecs->second.offset);
				modelMatrix[gotModelIndex->second] = glm::rotate(temp, rad, gotVecs->second.rotation);
			}

			float EntityRenderInfo::getRadian(std::string jointName) 
			{
				auto got = rotationRadian.find(jointName);
				if (got == rotationRadian.end()) 
				{
					throw std::runtime_error("unable to find the joint name: " + jointName);
				}

				return got->second;
			}

			const glm::mat4x4* EntityRenderInfo::getModelMatrixArr() 
			{
				return modelMatrix;
			}

			int EntityRenderInfo::getModelMatrixArrSize() 
			{
				return modelMatrixSize;
			}

			const int* EntityRenderInfo::getPathArr() 
			{
				return &(info->path[0]);
			}

			int EntityRenderInfo::getPathArrSize() 
			{
				return info->path.size();
			}

			const int* EntityRenderInfo::getPathIndexingArr() 
			{
				return info->pathRange;
			}

			int EntityRenderInfo::getPathIndexingArrSize() 
			{
				return info->pathRangeSize;
			}

			int EntityRenderInfo::getTextureID()
			{
				return info->textureID;
			}

			const wrapperGL::VAOID* EntityRenderInfo::getMeshID()
			{
				return info->vaoID;
			}

			void EntityRenderInfoMaker::init()
			{
				currentProgress.store(0);
			}

			float EntityRenderInfoMaker::getLoadingProgress() 
			{
				unsigned int temp = currentProgress.load();
				return (float)temp / static_cast<unsigned int>(EntityType::LAST);
			}


			EntityRenderInfo* EntityRenderInfoMaker::getEntityInfo(EntityType which) 
			{
				return protoTypeList[static_cast<unsigned int>(which)];
			}

			void EntityRenderInfoMaker::load() 
			{
				using namespace entityMakerTypes;

				//human
				{
					Joint* body = new Joint(glm::vec3(0.5, 0.95, 0.5), glm::vec3(0.0, 0.0, 1.0), "body", 0);

					auto leftArmXY = new Joint(glm::vec3(-0.25, 0.25, 0), glm::vec3(0.0, 0.0, 1.0), "leftArmXY");
					auto rightArmXY = new Joint(glm::vec3(0.25, 0.25, 0), glm::vec3(0.0, 0.0, 1.0), "rightArmXY");
					auto headXY = new Joint(glm::vec3(0.0, 0.25, 0), glm::vec3(0.0, 0.0, 1.0), "headXY");
					auto leftLegXY = new Joint(glm::vec3(-0.125, -0.25, 0), glm::vec3(0.0, 0.0, 1.0), "leftLegXY");
					auto rightLegXY = new Joint(glm::vec3(0.125, -0.25, 0), glm::vec3(0.0, 0.0, 1.0), "rightLegXY");

					body->children.push_back(leftArmXY);
					body->children.push_back(rightArmXY);
					body->children.push_back(headXY);
					body->children.push_back(leftLegXY);
					body->children.push_back(rightLegXY);

					leftArmXY->children.push_back(new Joint(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), "leftArmZY", 1));
					rightArmXY->children.push_back(new Joint(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), "rightArmZY", 2));
					headXY->children.push_back(new Joint(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), "headZY", 3));
					leftLegXY->children.push_back(new Joint(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), "leftLegZY", 4));
					rightLegXY->children.push_back(new Joint(glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), "rightLegZY", 5));

					protoTypeList[static_cast<unsigned int>(EntityType::HUMAN)] = makeRenderInfo(body, texture::TextureMaker::getTexture(texture::TextureMaker::TextureName::STONE), mesh::MeshMaker::getMesh(mesh::MeshMaker::MeshType::HUMAN));
					currentProgress++;
				}
			
			}

			EntityRenderInfo* EntityRenderInfoMaker::makeRenderInfo(entityMakerTypes::Joint* modelJoint, wrapperGL::TextureID tid, const wrapperGL::VAOID* vid)
			{
				auto counterTree = makeCounterTree(modelJoint);
				int modelSize = counterTree->modelMatrixCount;
				int meshSize = counterTree->meshCount;

				//if has empty size, just return
				if (modelSize <= 0) 
				{
					throw std::runtime_error("unable to make a render info with model size less than 1");
				}

				auto info = new entityMakerTypes::SharedInfo(vid);
				std::unordered_map<std::string, float> rProto;
				std::vector<int> step;

				info->pathRangeSize = meshSize * 2;
				info->pathRange = new int[meshSize * 2];
				info->textureID = tid.id;

				makeRenderInfo(counterTree, modelJoint, info, rProto, step, 0);

				//release memory
				freeTree(modelJoint, counterTree);
				delete modelJoint;
				delete counterTree;

				return new EntityRenderInfo(info, modelSize, rProto);
			}

			void EntityRenderInfoMaker::makeRenderInfo(entityMakerTypes::CounterNode* counterNode, entityMakerTypes::Joint* modelJoint, entityMakerTypes::SharedInfo* dest, std::unordered_map<std::string, float>& rProto, std::vector<int>& step, long currentOffset)
			{
			
				auto& name = modelJoint->name;
				auto offset = currentOffset;

				//map name to rotation vector, rotation radian vector, offset vector and model matrix
				dest->modelMatrixIndexing.insert({ name, offset} );
				dest->rotationOffsetVectors.insert({name, entityMakerTypes::RotationOffset(modelJoint->rotation, modelJoint->offset)} );
				rProto.insert({ name, 0.0 });

				//record step
				step.push_back(offset);

				//if current joint is bind to a mesh, then add all necessary steps to the path vector
				if (modelJoint->meshID >= 0) 
				{
					int begin = dest->path.size();
					for (auto& i : step) 
					{
						dest->path.push_back(i);
					}
					int end = dest->path.size();

					dest->pathRange[(modelJoint->meshID * 2)] = begin;
					dest->pathRange[(modelJoint->meshID * 2) + 1] = end;
				}
				
				//go inner nodes
				if (modelJoint->children.size() > 0) 
				{
					offset += 1;

					for (int i = 0; i < modelJoint->children.size();i++)
					{
						if (i > 0) 
						{
							offset += counterNode->children[i - 1]->modelMatrixCount;
						}

						makeRenderInfo(counterNode->children[i], modelJoint->children[i], dest, rProto, step, offset);
					}

				}
				step.pop_back();
			}

			entityMakerTypes::CounterNode* EntityRenderInfoMaker::makeCounterTree(entityMakerTypes::Joint* modelJoint) 
			{
				//base case
				if (modelJoint->children.size() <= 0) 
				{
					auto temp = new entityMakerTypes::CounterNode();
					temp->modelMatrixCount = 1;
					temp->meshCount = (modelJoint->meshID >= 0);
					return temp;
				}

				auto ret = new entityMakerTypes::CounterNode();
				int modelCount = 1;
				int meshCount = (modelJoint->meshID >= 0);

				//go inner nodes
				for (auto& e : modelJoint->children) 
				{
					auto temp = makeCounterTree(e);
					modelCount += temp->modelMatrixCount;
					meshCount += temp->meshCount;

					ret->children.push_back(temp);
				}
				ret->modelMatrixCount = modelCount;
				ret->meshCount = meshCount;
				return ret;
			}
			
			void EntityRenderInfoMaker::freeTree(entityMakerTypes::Joint* modelJoint, entityMakerTypes::CounterNode* counterNode) 
			{
				if (modelJoint == nullptr) return;

				for (int i = 0; i < modelJoint->children.size(); i++) 
				{
					freeTree(modelJoint->children[i], counterNode->children[i]);
				}

				for (int i = 0; i < modelJoint->children.size(); i++)
				{
					delete modelJoint->children[i];
					delete counterNode->children[i];
				}

			}
		}
	}
}