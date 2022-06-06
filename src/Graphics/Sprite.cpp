#include "Exstar/exstarglad/gl.h"

#include "Exstar/Graphics/TextureHandler.h"

#include "Exstar/Graphics/Sprite.h"

exstar::Sprite::Sprite(){}

exstar::Sprite::Sprite(std::string FILE){
	this->FILE = FILE;
	txHandler::generateTexture(FILE);
	txHandler::Texture tex = txHandler::getTexture(FILE);
	this->size = exstar::Dimension{tex.w,tex.h};
	loadShader(0,0,tex.w,tex.h,tex.w,tex.h);
}

exstar::Sprite::Sprite(std::string FILE, int x, int y, int width, int height){
	this->FILE = FILE;
	txHandler::generateTexture(FILE);
	txHandler::Texture tex = txHandler::getTexture(FILE);
	this->size = exstar::Dimension{width,height};
	loadShader(x,y,width,height,tex.w,tex.h);
}

exstar::Sprite::~Sprite(){
}

void exstar::Sprite::resize(int width, int height){
	size = exstar::Dimension{width, height};
}

void exstar::Sprite::resize(exstar::Dimension size){
	this->size = size;
}

int exstar::Sprite::getWidth() {
	return size.width ;
}

int exstar::Sprite::getHeight(){
	return size.height;
}

exstar::Dimension exstar::Sprite::getSize(){
	return size;
}

unsigned int exstar::Sprite::getVAO(){
	return VAO;
}

void exstar::Sprite::Bind(){
	glActiveTexture(GL_TEXTURE0);
	txHandler::Texture tex = txHandler::getTexture(this->FILE);
	glBindTexture(GL_TEXTURE_2D, tex.texture);
}

void exstar::Sprite::loadShader(int x,int y,int width, int height,int imageW, int imageH){
	exstar::Point Pos = exstar::Point{x,y};
	exstar::Dimension textureSize = exstar::Dimension{imageW, imageH};

	//Define the sides of the sprite to load
	float lx,ty,rx,by;
	lx =  (Pos.x + 0.5)/(textureSize.width*1.0f) ;
	ty =  (Pos.y + 0.5)/(textureSize.height*1.0f);
	rx = (Pos.x + size.width*1.0f)/(textureSize.width*1.0f)  ;
	by = (Pos.y + size.height*1.0f)/(textureSize.height*1.0f);

	float vertices[] = {
		0.0f, 1.0f, lx, by,
		1.0f, 0.0f, rx, ty,
		0.0f, 0.0f, lx, ty,

		0.0f, 1.0f, lx, by,
		1.0f, 1.0f, rx, by,
		1.0f, 0.0f, rx, ty
	};

	//Prepare Buffers
	glGenVertexArrays(1, &this->VAO);

	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    // texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(1);

}
