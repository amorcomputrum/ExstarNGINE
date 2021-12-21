#include "Exstar/Utils/Math.h"
#include "Exstar/Utils/Vector2d.h"

exstar::Vector2d::Vector2d(double x,double y){
	this->x = x;
	this->y = y;
}
float exstar::Vector2d::magnitude(){
	return std::sqrt((x*x) + (y*y));
}
float exstar::Vector2d::sqrMagnitude(){
	return ((x*x) + (y*y));
}
void exstar::Vector2d::set(double x,double y){
	this->x = x;
	this->y = y;
}
double exstar::Vector2d::getX(){
	return x;
}
double exstar::Vector2d::getY(){
	return y;
}
exstar::Vector2d exstar::Vector2d::operator+(exstar::Vector2d param){
	return exstar::Vector2d(x + param.x,y + param.y);
}
exstar::Vector2d exstar::Vector2d::operator+(double param){
	return exstar::Vector2d(x + param,y + param);
}
exstar::Vector2d exstar::Vector2d::operator-(exstar::Vector2d param){
	return exstar::Vector2d(x - param.x,y - param.y);
}
exstar::Vector2d exstar::Vector2d::operator-(double param){
	return exstar::Vector2d(x - param,y - param);
}
exstar::Vector2d exstar::Vector2d::operator/(exstar::Vector2d param){
	return exstar::Vector2d(x/param.x,y/param.y);
}
exstar::Vector2d exstar::Vector2d::operator/(double param){
	return exstar::Vector2d(x/param,y/param);
}
exstar::Vector2d exstar::Vector2d::operator*(exstar::Vector2d param){
	return exstar::Vector2d(x*param.x,y*param.y);
}
exstar::Vector2d exstar::Vector2d::operator*(double param){
	return exstar::Vector2d(x*param,y*param);
}
float exstar::Vector2d::dot(exstar::Vector2d vec1,exstar::Vector2d vec2){
	return (vec1.x*vec2.x) + (vec2.y*vec1.y);
}
float exstar::Vector2d::cross(exstar::Vector2d vec1,exstar::Vector2d vec2){
	return (a.x * b.y) - (a.y - b.x);
}
exstar::Vector2d exstar::Vector2d::cross(exstar::Vector2d vec,float s){
	return exstar::Vector2d(s*vec.y,-s*vec.x);
}
exstar::Vector2d exstar::Vector2d::normalize(exstar::Vector2d vec){
	return (vec * (1/vec.magnitude()));
}