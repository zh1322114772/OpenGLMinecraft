#pragma once
#include "GLW_Types.hpp"
#include <vector>
#include <initializer_list>
namespace other
{
	struct At 
	{
		wrapperGL::ImageObject* img;
		unsigned int X;
		unsigned int Y;

		At(wrapperGL::ImageObject* org, unsigned int x, unsigned int y) : img(org), X(x), Y(y) 
		{
		
		}
	};


	/// <summary>
	/// this class process images
	/// </summary>
	class BitMapProcess
	{

	public:
		/// <summary>
		/// merge multiple bitmaps into one
		/// </summary>
		/// <param name="list"></param>
		static wrapperGL::ImageObject* merge(std::initializer_list<At> list);

		/// <summary>
		/// convert rgb format to rgba format
		/// </summary>
		/// <param name="i"></param>
		/// <returns></returns>
		static wrapperGL::ImageObject* RGB2RGBA(wrapperGL::ImageObject* i);

		/// <summary>
		/// select specific image channel from multiple srouces and combine to single RGBA image
		/// ensure that all sources have same size
		/// </summary>
		/// <param name="sourceA">source a </param>
		/// <param name="channelA">specific channel from sourceA</param>
		/// <param name="sourceB">source b</param>
		/// <param name="channelB">specific channel from sourceB</</param>
		/// <param name="sourceC">source C</param>
		/// <param name="channelC">specific channel from sourceC</param>
		/// <param name="sourceD">source D</param>
		/// <param name="channelD">specific channel from sourceD</param>
		/// <returns></returns>
		static wrapperGL::ImageObject* ChannelMerge(wrapperGL::ImageObject* sourceA, char channelA, wrapperGL::ImageObject* sourceB, char channelB, wrapperGL::ImageObject* sourceC, char channelC, wrapperGL::ImageObject* sourceD, char channelD);
	};
}