#include "Exstar/Utils/Math.h"
#include "Exstar/Utils/Vector2d.h"

exstar::Vector2d::Vector2d(int x,int y){
	data[0] = x;
	data[1] = y;
}
float exstar::Vector2d::dot(exstar::Vector2d v){
	return (getX()*v.getY()) + (v.getX() * getY());
}
float exstar::Vector2d::magnitude(){
	return std::sqrt((data[0]*data[0]) + (data[1]*data[1]));
}
void exstar::Vector2d::add(exstar::Vector2d vec){
	data[0] += vec.getX();
	data[1] += vec.getY();
}
void exstar::Vector2d::add(int x,int y){
	data[0] += x;
	data[1] += y;
}
void exstar::Vector2d::min(exstar::Vector2d vec){
	data[0] -= vec.getX();
	data[1] -= vec.getY();
}
void exstar::Vector2d::min(int x,int y){
	data[0] -= x;
	data[1] -= y;
}
void exstar::Vector2d::mul(exstar::Vector2d vec){
	data[0] *= vec.getX();
	data[1] *= vec.getY();
}
void exstar::Vector2d::mul(int x,int y){
	data[0] *= x;
	data[1] *= y;
}
void exstar::Vector2d::div(exstar::Vector2d vec){
	data[0] /= vec.getX();
	data[1] /= vec.getY();
}
void exstar::Vector2d::div(int x,int y){
	data[0] /= x;
	data[1] /= y;
}
void exstar::Vector2d::set(int x,int y){
	data[0] = x;
	data[1] = y;
}
int exstar::Vector2d::getX(){
	return data[0];
}
int exstar::Vector2d::getY(){
	return data[1];
}