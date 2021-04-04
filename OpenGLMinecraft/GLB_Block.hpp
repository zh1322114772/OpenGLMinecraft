#pragma once

namespace global
{
	namespace resource
	{
		namespace block 
		{
		
			class BlockRenderInfo final
			{
			public:
				/// <summary>
				/// block type
				/// </summary>
				const unsigned short int TYPE_BLOCK = 0b0;
				const unsigned short int TYPE_LIQUID = 0b1;

				/// <summary>
				/// additional block attachment
				/// </summary>
				const unsigned short int ATTACHMENT_INVISIBLE = 0b00;
				const unsigned short int ATTACHMENT_VISIBLE = 0b10;
				const unsigned short int ATTACHMENT_TRANSPARENT = 0b100;
				const unsigned short int ATTACHMENT_RELFECT = 0b1000;

			private:
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


			public:

				/// <summary>
				/// get texture id
				/// </summary>
				/// <returns></returns>
				const unsigned int& getTextureID();

				/// <summary>
				/// get normal map id
				/// </summary>
				/// <returns></returns>
				const unsigned int& getNormalID();

				/// <summary>
				/// get occlusion & specular map
				/// </summary>
				/// <returns></returns>
				const unsigned int& getOSID();

				/// <summary>
				/// constructor
				/// </summary>
				/// <param name="tid">texture id</param>
				/// <param name="nid">normal id</param>
				/// <param name="osid">occlusion&specular id</param>
				/// <returns></returns>
				BlockRenderInfo(unsigned int tid, unsigned int nid, unsigned short int osid) :textureID(tid), normalID(nid), OSID(osid)
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
				BlockRenderInfo(unsigned int tid, unsigned int nid, unsigned int osid, unsigned short int t) : properties(t), textureID(tid), normalID(nid), OSID(osid)
				{

				}
			};
		
			/// <summary>
			/// this class make block render info
			/// </summary>
			class BlockRenderInfoMaker final
			{
			public:
				enum class BlockType
				{
					AIR,
					STONE,
					DIRT,
					COBBLESTONE,
					OAK_PLANKS,
					SPRUCE_PLANKS,
					BRICH_PLANKS,
					JUNGLE_PLANKS,
					ACACIA_PLANKS,
					DARK_OAK_PLANKS,
					BEDROCK,
					SAND,
					GRASS,
					COBBLESTONE_MOSSY,
					WATER,

					LAST
				};

				/// <summary>
				/// load all block render info prototypes
				/// </summary>
				static void load();

				/// <summary>
				/// return block render info
				/// </summary>
				/// <param name="which">which block</param>
				/// <returns></returns>
				static BlockRenderInfo* getBlockRenderInfo(BlockType which);

			private:
				static BlockRenderInfo* list[static_cast<unsigned int>(BlockType::LAST)];

			
			};
		
		}
	}

}