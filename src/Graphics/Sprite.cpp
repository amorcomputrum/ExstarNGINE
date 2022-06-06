#define STB_IMAGE_IMPLEMENTATION

#include "Exstar/Graphics/stb_image.h"

#include "Exstar/exstarglad/gl.h"

#include "Exstar/Graphics/Sprite/HandlerToSprite.h"
#include "Exstar/Graphics/Sprite/Image_Handler.h"

#include "Exstar/Graphics/Sprite.h"

exstar::Sprite::Sprite(){}

exstar::Sprite::Sprite(std::string FILE){
	int w,h,type;
	unsigned char* data = stbi_load(FILE.c_str(), &w, &h, &type, 0);
	loadShader(0,0,w,h,w,h,type,data);
}

exstar::Sprite::Sprite(std::string FILE, int x, int y, int width, int height){
	int w,h,type;
	unsigned char* data = stbi_load(FILE.c_str(), &w, &h, &type, 0);
	loadShader(x,y,width,height,w,h,type,data);
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
	glBindTexture(GL_TEXTURE_2D, texture);
}

void exstar::Sprite::loadShader(int x,int y,int width, int height,int imageW, int imageH,int type,unsigned char* data){
	

	size = exstar::Dimension{width,height};
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

	//Load Texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST              );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST              );

    //Load Sprite according to its type(RGB,RGBA)
	if(type == 3){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB , textureSize.width, textureSize.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}else{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSize.width, textureSize.height, 0, GL_RGBA,GL_UNSIGNED_BYTE, data);
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}
