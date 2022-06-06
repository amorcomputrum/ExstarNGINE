#define STB_IMAGE_IMPLEMENTATION

#include "Exstar/Graphics/stb_image.h"
#include "Exstar/exstarglad/gl.h"

#include "Exstar/Graphics/TextureHandler.h"

txHandler::Texture::Texture(){}

txHandler::Texture::Texture(std::string filename){
	unsigned char* data = stbi_load(filename.c_str(), &w, &h, &type, 0);

	//Load Texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST              );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST              );

    //Load Sprite according to its type(RGB,RGBA)
	if(type == 3){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB , w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}else{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,GL_UNSIGNED_BYTE, data);
	}
	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	this->FILE = filename;
}

void txHandler::generateTexture(std::string filename){
	//check if texture exists
	if(textures.size != 0){
		for(int i = 0; i < textures.size; i++){
			if(textures.get(i).FILE == filename) return;
		}
	}
	//if it does not then generate and store new texture
	textures.add(txHandler::Texture(filename));
}

txHandler::Texture txHandler::getTexture(std::string filename){
	//return texture info of file
	for(int i = 0; i < textures.size; i++){
		if(textures.get(i).FILE == filename) return textures.get(i);
	}
}