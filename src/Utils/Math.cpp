#include "Exstar/Utils/Math.h"

double exstar::Distance(double x1,double y1,double x2, double y2){
	return sqrt(pow(x2 - x1,2) + pow(y2 - y1,2));
}
double exstar::Distance(exstar::Vector2d pos1,exstar::Vector2d pos2){
	return exstar::Distance(pos1.x,pos1.y,pos2.x,pos2.y);
}
int exstar::Random(int min,int max){
	return rand() % (max - min + 1) + min;
}