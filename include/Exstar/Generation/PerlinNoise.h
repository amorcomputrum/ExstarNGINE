#ifndef EXSTAR_PERLINNOISE_H
#define EXSTAR_PERLINNOISE_H
#include <vector>

namespace exstar{
	class PerlinNoise{
	public:
		PerlinNoise();
		PerlinNoise(unsigned int seed);
		double noise(double x);
		double noise(double x,double y);
		double noise(double x,double y,double z);
	private:
		std::vector<int> permutation;
		double fade(double t);
		double lerp(double t,double a,double b);
		double grad(int hash,double x,double y,double z);
	};
}


#endif