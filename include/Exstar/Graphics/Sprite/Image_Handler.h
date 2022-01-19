#pragma once

#include "Exstar/Graphics/Sprite/HandlerToSprite.h"
#include "Exstar/Utils/ArrayList.h"

namespace exstar{
	/**
	 * The images data
	*/
	extern exstar::ArrayList<unsigned char *>* images;
	/**
	 * The amount of Objects that are using each file that is stored in the images ArrayList
	*/
	extern exstar::ArrayList<int>* numUses;
	/**
	 * Add an image to the images ArrayList
	 * 
	 * @param File The File to load
	 * 
	 * @return The index,width, and height of the File
	*/
	exstar::sprite::HandlerToSprite addImage(const char* FILE);
	/**
	 * Removes an image from the images ArrayList
	 * 
	 * @param index The location of the image to remove
	*/
	void removeImage(int index);
}
