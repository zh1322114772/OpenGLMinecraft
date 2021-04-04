#include "GLB_Texture.hpp"
#include "BitMapProcess.hpp"
#include "GLW_GLWrapper.hpp"
using namespace wrapperGL;

#define BLOCK_PATH "data\\textures\\blocks\\"
#define BLOCK_LOAD_ALL(t, n, o, s, file_name) t = GLWrapper::loadImage(BLOCK_PATH#file_name".png"); n = GLWrapper::loadImage(BLOCK_PATH#file_name"_n.png"); o = GLWrapper::loadImage(BLOCK_PATH#file_name"_o.png"); s = GLWrapper::loadImage(BLOCK_PATH#file_name"_s.png");
#define BLOCK_UNLOAD_ALL(t, n, o, s) delete t; delete n; delete o; delete s


namespace global
{
	namespace resource
	{
		namespace texture
		{
			void TextureMaker::init() 
			{
				currentProgress.store(0);
			}

			void TextureMaker::load() 
			{
				
				TextureID* tid;

				ImageObject* imga;
				ImageObject* imgb;
				ImageObject* imgc;
				ImageObject* imgd;
				ImageObject* imge;
				ImageObject* imgf;
				ImageObject* imgg;
				ImageObject* imgh;


				//load stone
				LOAD_BLOCK_ALL(imga, imgb, imgc, imgd, stone);

			}




		}
	}
}