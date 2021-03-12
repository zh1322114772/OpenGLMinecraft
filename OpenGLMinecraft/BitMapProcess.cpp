#pragma once
#include "BitMapProcess.hpp"
#include <stdexcept>
#include <iostream>
namespace other 
{
	wrapperGL::ImageObject* BitMapProcess::merge(std::initializer_list<At> list) 
	{
		int width = 0;
		int	height = 0;

		for (auto i = list.begin(); i < list.end(); i++) 
		{
			//ensure is rgba format
			if ((*i).img->format != 4) 
			{
				throw std::runtime_error("Unable to process the image with channels of " + (*i).img->format);
			}

			width += (*i).img->width;

			if ((*i).img->height > height) 
			{
				height = (*i).img->height;
			}
		}
	
		//check size
		if (width == 0 || height == 0 || width > 8192 || height > 8192) 
		{
			throw std::runtime_error("Maximum or minimum size reached");
		}

		//final image
		wrapperGL::ImageObject* res = new wrapperGL::ImageObject();
		res->format = 4;
		res->height = height;
		res->width = width;
		res->img_arr = (unsigned char*) malloc(height * width * 4);

		
		for (int i = 0; i < height; i ++) 
		{
			//initial location of every row
			auto ptr = (res->img_arr + (i * width * 4));

			//paste row from source
			for (auto iter = list.begin(); iter < list.end(); iter++)
			{

				auto source = (*iter);

				//check y
				if (!(i >= source.Y && i < (source.Y + source.img->height))) 
				{
					continue;
				}

				auto sptr = (source.img->img_arr + ((i - source.Y) * source.img->width * 4));

				//if the width of the source image exceeds the width of the final image
				int exceed = (source.X + source.img->width) - res->width;


				if (exceed > 0)
				{
					memcpy(ptr + (source.X * 4), sptr, (source.img->width - exceed) * 4);
				}
				else
				{
					memcpy(ptr + (source.X * 4), sptr, (source.img->width) * 4);
				}
			}
			
			
		}
		
		return res;
	}

	wrapperGL::ImageObject* BitMapProcess::RGB2RGBA(wrapperGL::ImageObject* i) 
	{
		if (i->format != 3) 
		{
			throw std::runtime_error("ImageObject must be a rgb image");
		}
	
		wrapperGL::ImageObject* ret = new wrapperGL::ImageObject();
		ret->format = 4;
		ret->width = i->width;
		ret->height = i->height;
		ret->img_arr = (unsigned char*)malloc(ret->width * ret->height * 4);

		for (int j = 0; j < ret->width * ret->height; j++) 
		{
			memcpy(ret->img_arr + (j * 4), i->img_arr + (j * 3), 3);

			//set alpha
			ret->img_arr[(j * 4) + 3] = 255;
		}

		return ret;
	}

	wrapperGL::ImageObject* BitMapProcess::ChannelMerge(wrapperGL::ImageObject* sourceA, char channelA, wrapperGL::ImageObject* sourceB, char channelB, wrapperGL::ImageObject* sourceC, char channelC, wrapperGL::ImageObject* sourceD, char channelD) 
	{
		if (sourceA == nullptr) 
		{
			throw std::runtime_error("least needs one source");
		}

		wrapperGL::ImageObject* ret = new wrapperGL::ImageObject();
		ret->format = 4;
		ret->width = sourceA->width;
		ret->height = sourceA->height;
		ret->img_arr = (unsigned char*)malloc(ret->width * ret->height * 4);
	
		int totalPixels = ret->width * ret->height;

		//fill red channel
		for (int i = 0; i < totalPixels; i++) 
		{
			ret->img_arr[i * 4] = sourceA->img_arr[(i * 4) + channelA];
		}
		
		//fill green channel
		if (sourceB != nullptr) 
		{
			for (int i = 0; i < totalPixels; i++)
			{
				ret->img_arr[(i * 4) + 1] = sourceB->img_arr[(i * 4) + channelB];
			}
		}
		
		//fill blue channel
		if (sourceC != nullptr)
		{
			for (int i = 0; i < totalPixels; i++)
			{
				ret->img_arr[(i * 4) + 2] = sourceC->img_arr[(i * 4) + channelC];
			}
		}

		//fill alpha channel
		if (sourceD != nullptr)
		{
			for (int i = 0; i < totalPixels; i++)
			{
				ret->img_arr[(i * 4) + 3] = sourceD->img_arr[(i * 4) + channelD];
			}
		}

		return ret;
	}
}