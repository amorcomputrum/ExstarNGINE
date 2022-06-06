#pragma once

#include "Exstar/Utils/ArrayList.h"

#include <string>

namespace txHandler{
	class Texture{
	public:
		int w,h,type;
		std::string FILE;
		unsigned int texture;
		Texture();
		Texture(std::string filename);
	};
	static exstar::ArrayList<Texture> textures = exstar::ArrayList<Texture>();
	void generateTexture(std::string filename);
	Texture getTexture(std::string filename);
}