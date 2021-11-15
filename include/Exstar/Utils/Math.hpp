#include <cmath>
#include <stdlib.h>
namespace exstar{
	const double EULER = 2.71828182845904523536;
	double Distance(double x1,double y1,double x2, double y2){
		return sqrt(pow(x2-x1,2) + pow(y2-y1,2));
	}

	int Random(int min,int max){
		return rand() % (max - min +1)+min;
	}
}