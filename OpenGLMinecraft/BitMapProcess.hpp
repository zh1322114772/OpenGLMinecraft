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
		static wrapperGL::ImageObject* rgb2rgba(wrapperGL::ImageObject* i);

		/// <summary>
		/// select specific image channel from multiple srouces and combine it into a single RGBA image
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
		static wrapperGL::ImageObject* channelMerge(wrapperGL::ImageObject* sourceA, char channelA, wrapperGL::ImageObject* sourceB, char channelB, wrapperGL::ImageObject* sourceC, char channelC, wrapperGL::ImageObject* sourceD, char channelD);

		/// <summary>
		/// copy image
		/// </summary>
		/// <param name="s"></param>
		/// <returns></returns>
		static wrapperGL::ImageObject* copy(wrapperGL::ImageObject* s);

		/// <summary>
		/// horizontally rotate normal map
		/// </summary>
		/// <param name="s">normal map</param>
		/// <param name="clockWise">clockwise rotation or counterclockwise rotation</param>
		/// <returns>rotated normal map</returns>
		static wrapperGL::ImageObject* normalHorizontalRotate(wrapperGL::ImageObject* s, bool clockwise);

		/// <summary>
		/// vertically rotate normal map
		/// </summary>
		/// <param name="s">normal map</param>
		/// <param name="clockWise">clockwise rotation or counterclockwise rotation</param>
		/// <returns></returns>
		static wrapperGL::ImageObject* normalVerticalRotate(wrapperGL::ImageObject* s, bool clockwise);
	};
}