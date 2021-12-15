#include "Exstar/Sprite/Image_Handler.h"
#include "Exstar/Sprite/Sprite.h"
exstar::Sprite::Sprite(const char* file){
	file = file;
	int* feedback = exstar::addImage(file);
	fileIndex = feedback[0];
	size = exstar::Dimension{feedback[1],feedback[2]};
	textureSize = exstar::Dimension{feedback[1],feedback[2]};
	type = feedback[3];
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
int exstar::Sprite::getType(){
	return type;
}
unsigned char * exstar::Sprite::getImage(){
	return exstar::images->get(fileIndex);
}