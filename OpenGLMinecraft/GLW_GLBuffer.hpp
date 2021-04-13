#pragma once
#include <unordered_map>
#include <tuple>
#include <string>

#include "GLW_GlmHeaders.hpp"

namespace wrapperGL
{
	namespace glBufferTypes 
	{
		template<int size, typename... types>
		struct BufferElementBase 
		{
			const static auto groupSize = sizeof...(types);
			static_assert(((size > 0) && (size < 9)), "type group size error");

			using typeGroup = std::tuple<types...>;
		};

		template<typename a>
		struct BufferElement1 : BufferElementBase<1, a>
		{
			a var1;
		};

		template<typename a, typename b>
		struct BufferElement2 : BufferElementBase <2, a, b>
		{
			a var1;
			b var2;
		};
	
		template<typename a, typename b, typename c>
		struct BufferElement3 : BufferElementBase <3, a, b, c>
		{
			a var1;
			b var2;
			c var3;
		};

		template<typename a, typename b, typename c, typename d>
		struct BufferElement4 : BufferElementBase <4, a, b, c, d>
		{
			a var1;
			b var2;
			c var3;
			d var4;
		};

		template<typename a, typename b, typename c, typename d, typename e>
		struct BufferElement5 : BufferElementBase <5, a, b, c, d, e>
		{
			a var1;
			b var2;
			c var3;
			d var4;
			e var5;
		};

		template<typename a, typename b, typename c, typename d, typename e, typename f>
		struct BufferElement6 : BufferElementBase <6, a, b, c, d, e, f>
		{
			a var1;
			b var2;
			c var3;
			d var4;
			e var5;
			f var6;
		};

		template<typename a, typename b, typename c, typename d, typename e, typename f, typename g>
		struct BufferElement7 : BufferElementBase <7, a, b, c, d, e, f, g>
		{
			a var1;
			b var2;
			c var3;
			d var4;
			e var5;
			f var6;
			g var7;
		};

		template<typename a, typename b, typename c, typename d, typename e, typename f, typename g, typename h>
		struct BufferElement8 : BufferElementBase <8, a, b, c, d, e, f, g, h>
		{
			a var1;
			b var2;
			c var3;
			d var4;
			e var5;
			f var6;
			g var7;
			h var8;
		};

		template<unsigned int length, typename t>
		struct Buffer 
		{
			static_assert(std::is_base_of(BufferElementBase, t), "Buffer must have BufferElement type");
			t bufferElement[length];
			const unsigned int size = length;
		};

		/// <summary>
		/// define buffer element for block
		/// position, normal vector, texture coordinates, block face, extra
		/// </summary>
		using BlockBufferElement = BufferElement5<glm::vec3, glm::vec3, glm::vec2, float, float>;

	}


	class glBuffer
	{

	public:

		
	
	
	};


}