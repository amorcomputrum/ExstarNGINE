#include "Exstar/exstarglad/gl.h"

#include "Exstar/Graphics/Sprite/HandlerToSprite.h"
#include "Exstar/Graphics/Sprite/Image_Handler.h"

#include "Exstar/Graphics/Sprite/Sprite.h"

exstar::Sprite::Sprite(){}

exstar::Sprite::Sprite(std::string FILE){
	this->FILE    = FILE;
	exstar::sprite::HandlerToSprite feedback = exstar::addImage(FILE);
	fileIndex     = feedback.index;
	size          = exstar::Dimension{feedback.width, feedback.height};
	cutSize       = exstar::Dimension{feedback.width, feedback.height};
	textureSize   = exstar::Dimension{feedback.width, feedback.height};
	type          = feedback.type;
	Pos           = exstar::Point{0,0};
	loadShader();
}

exstar::Sprite::Sprite(std::string FILE, int x, int y, int w, int h){
	this->FILE    = FILE;
	exstar::sprite::HandlerToSprite feedback = exstar::addImage(FILE);
	fileIndex     = feedback.index;
	size          = exstar::Dimension{w, h};
	cutSize       = exstar::Dimension{w, h};
	textureSize   = exstar::Dimension{feedback.width, feedback.height};
	type          = feedback.type;
	Pos           = exstar::Point{x,y};
	loadShader();
}

exstar::Sprite::~Sprite(){
	removeImage(fileIndex);
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

void exstar::Sprite::loadShader(){
	
	//Define the sides of the sprite to load
	float lx,ty,rx,by;
	lx =  (Pos.x + 0.5)/(textureSize.width*1.0f) ;
	ty =  (Pos.y + 0.5)/(textureSize.height*1.0f);
	rx = (Pos.x + cutSize.width*1.0f)/(textureSize.width*1.0f)  ;
	by = (Pos.y + cutSize.height*1.0f)/(textureSize.height*1.0f);

	float vertices[] = {
		0.0f, 1.0f, lx, by,
		1.0f, 0.0f, rx, ty,
		0.0f, 0.0f, lx, ty,

		0.0f, 1.0f, lx, by,
		1.0f, 1.0f, rx, by,
		1.0f, 0.0f, rx, ty
	};

	//unsigned int indices[] = {0, 1, 3, 1, 2, 3};
	//Prepare Buffers
	glGenVertexArrays(1, &this->VAO);

	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

    // texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(1);

	//Load Texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

    // set texture filtering parameters
    
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE            );	
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE            ); 

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST              );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST              );

    //Load Sprite according to its type(RGB,RGBA)
	if(type == 3){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB , textureSize.width, textureSize.height, 0, GL_RGB, GL_UNSIGNED_BYTE, exstar::images->get(fileIndex));
		glGenerateMipmap(GL_TEXTURE_2D);
	}else{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureSize.width, textureSize.height, 0, GL_RGBA,GL_UNSIGNED_BYTE, exstar::images->get(fileIndex));
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, 0);
}
