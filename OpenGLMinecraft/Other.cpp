#include "Other.hpp"
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
}
