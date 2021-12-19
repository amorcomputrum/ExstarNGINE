#include "Exstar/Utils/Math.h"

double exstar::Distance(double x1,double y1,double x2, double y2){
	return sqrt(pow(x2 - x1,2) + pow(y2 - y1,2));
}

int exstar::Random(int min,int max){
	return rand() % (max - min + 1) + min;
}