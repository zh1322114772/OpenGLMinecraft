#pragma once
#include "GLW_GlmHeaders.hpp"
namespace other 
{

	class Other{
	public:
		/// <summary>
		/// generates a random number based on the seed and x
		/// </summary>
		/// <param name="seed">random seed</param>
		/// <param name="x">value x</param>
		/// <returns></returns>
		static unsigned int randomGenerator(unsigned long long seed, long long x);

		/// <summary>
		/// generates a random float between 0-1
		/// </summary>
		/// <param name="seed">random seed</param>
		/// <param name="x">value x</param>
		/// <returns></returns>
		static float randomGeneratorF(unsigned long long seed, long long x);

		/// <summary>
		/// gaussian similarity function
		/// </summary>
		/// <param name="x">x vector</param>
		/// <param name="l">l vector</param>
		/// <param name="sigma">sigma</param>
		/// <returns></returns>
		static float gaussianSimilarity(glm::vec2 x, glm::vec2 l, float sigma);

		/// <summary>
		/// calculate the impurity of vec4
		/// </summary>
		/// <param name="x">vec4</param>
		/// <returns></returns>
		static float giniImpurity(glm::vec4 x);

		/// <summary>
		/// sigmoid function
		/// </summary>
		/// <param name="x">val</param>
		/// <returns></returns>
		static float sigmoid(float x);

		/// <summary>
		///  relu function
		/// </summary>
		/// <param name="x"></param>
		/// <param name="at"></param>
		/// <returns></returns>
		static float relu(float x, float centeredAt);

		/// <summary>
		/// smooth function
		/// </summary>
		/// <param name="x"></param>
		/// <returns></returns>
		static float smooth(float x, float coef);
	};
	
}