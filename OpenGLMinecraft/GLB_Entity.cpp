#include "GLB_Entity.hpp"

namespace global
{
	namespace resource
	{
		namespace entity
		{
			EntityRenderInfo EntityRenderInfoMaker::protoTypeList[static_cast<unsigned int>(EntityType::LAST)];

			void EntityRenderInfoMaker::makeRenderInfo(entityMakerTypes::Joint* modelJoint, EntityRenderInfo& dest) 
			{
				auto counterTree = makeCounterTree(modelJoint);
				int modelSize = counterTree->modelMatrixCount;
				int meshSize = counterTree->meshCount;

				//if has empty size, just return
				if (modelSize <= 0) return;

				auto info = new entityMakerTypes::SharedInfo();
				std::unordered_map<std::string, float> rProto;
				std::vector<unsigned int> step;

				info->pathRangeSize = meshSize * 2;
				info->pathRange = new int[meshSize * 2];


				makeRenderInfo(counterTree, modelJoint, info, rProto, step, 0);

				//write destination
				dest = EntityRenderInfo(info, modelSize, rProto);
	
			}

			void EntityRenderInfoMaker::makeRenderInfo(entityMakerTypes::CounterNode* counterNode, entityMakerTypes::Joint* modelJoint, entityMakerTypes::SharedInfo* dest, std::unordered_map<std::string, float>& rProto, std::vector<unsigned int>& step, long currentOffset)
			{
			
				auto& name = modelJoint->name;
				auto offset = currentOffset;

				//map names to rotation vector, rotation radian vector, offset vector and model matrix
				dest->modelMatrixIndexing.insert({ { name, offset} });
				dest->rotationOffsetVectors->insert({ {name, std::make_tuple(modelJoint->rotation, modelJoint->offset)} });
				rProto.insert({ { name, 0.0} });

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

		}
	}
}