#include "Other.hpp"
#include <math.h>
namespace other 
{
	unsigned int Other::randomGenerator(unsigned long long seed, long long l)
	{
		unsigned long long num = (seed * l) + seed;
		unsigned ret = 0;

		for (int i = 0; i < 32; i++)
		{
			num = (num << (num % 7)) + ((seed + num) % 255);
			ret <<= 1;
			ret += (num & 0b1);
		}

		return ret;
	}

	float Other::randomGeneratorF(unsigned long long seed, long long x)
	{
		return (float)randomGenerator(seed, x) / 0xffffffff;
	}


	float Other::gaussianSimilarity(glm::vec2 x, glm::vec2 l, float sigma) 
	{
		return exp(-powf(glm::length(x - l), 2) / (2 * powf(sigma, 2)));
	}

	float Other::giniImpurity(glm::vec4 x) 
	{
		float sum = x[0] + x[1] + x[2] + x[3];
		x = x / sum;
		return 1 - glm::dot(x, x);
	}

	float Other::sigmoid(float x) 
	{
		return 1 / (1 + std::exp(-x));
	}

	float Other::relu(float x, float c) 
	{
		x -= c;
		if (x < 0) 
		{
			return 0;
		}
		else 
		{
			return x;
		}
	}

	float Other::smooth(float x, float coef) 
	{
		return (1 / (1 - powf(2, powf(x, coef) + 1))) + 1;
	}
}
