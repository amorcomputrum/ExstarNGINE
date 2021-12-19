#include "Exstar/Sprite/Image_Handler.h"
#include "Exstar/Sprite/Sprite.h"

exstar::Sprite::Sprite(const char* file){
	file = file;
	int* feedback = exstar::addImage(file);
	fileIndex = feedback[0];
	size = exstar::Dimension{feedback[1],feedback[2]};
	cutSize = exstar::Dimension{feedback[1],feedback[2]};
	textureSize = exstar::Dimension{feedback[1],feedback[2]};
	type = feedback[3];
	Pos = exstar::Point{0,0};
}
exstar::Sprite::Sprite(const char* file,int x,int y,int w,int h){
	file = file;
	int* feedback = exstar::addImage(file);
	fileIndex = feedback[0];
	size = exstar::Dimension{w,h};
	cutSize = exstar::Dimension{w,h};
	textureSize = exstar::Dimension{feedback[1],feedback[2]};
	type = feedback[3];
	Pos = exstar::Point{x,y};
}
exstar::Sprite::~Sprite(){
	removeImage(fileIndex);
}
void exstar::Sprite::resize(int width,int height){
	size = exstar::Dimension{width,height};
}
void exstar::Sprite::resize(exstar::Dimension size){
	this->size = size;
}
int exstar::Sprite::getTextureWidth(){
	return textureSize.width;
}
int exstar::Sprite::getTextureHeight(){
	return textureSize.height;
}
exstar::Dimension exstar::Sprite::getTextureSize(){
	return textureSize;
}
int exstar::Sprite::getWidth(){
	return size.width;
}
int exstar::Sprite::getHeight(){
	return size.height;
}
exstar::Dimension exstar::Sprite::getSize(){
	return size;
}
exstar::Dimension exstar::Sprite::getCut(){
	return cutSize;
}
exstar::Point exstar::Sprite::getPos(){
	return Pos;
}
int exstar::Sprite::getType(){
	return type;
}
unsigned char * exstar::Sprite::getImage(){
	return exstar::images->get(fileIndex);
}