#define STB_IMAGE_IMPLEMENTATION

#include "Exstar/Graphics/Sprite/stb_image.h"
#include "Exstar/Utils/Exception.h"

#include "Exstar/Graphics/Sprite/Image_Handler.h"

//Define Variables
exstar::ArrayList<unsigned char *>* exstar::images  = new exstar::ArrayList<unsigned char *>();
exstar::ArrayList<int>*             exstar::numUses = new exstar::ArrayList<int>();

exstar::sprite::HandlerToSprite exstar::addImage(const char* FILE){
	//load data
	int w,h,type;

	unsigned char* data = stbi_load(FILE, &w, &h, &type, 0);
	if(!data){
		throw exstar::exception("exstar::addImage - Image failed to load");
	}
	//check if already in images
	for(int i = 0; i < exstar::images->size; i++){
		if(exstar::images->get(i) == data){
			exstar::numUses->replace(i, exstar::numUses->get(i) + 1);

			return exstar::sprite::HandlerToSprite{i, w, h, type};
		}
	}

	exstar::images->add(data);
	exstar::numUses->add(1);

	return exstar::sprite::HandlerToSprite{exstar::images->size - 1, w, h, type};
}

void exstar::removeImage(int index){
	//Update Number of Uses
	if(exstar::numUses->get(index) - 1 <= 0){
		stbi_image_free(exstar::images->get(index));
		exstar::images->remove(index );
		exstar::numUses->remove(index);
	}else{
		exstar::numUses->replace(index, exstar::numUses->get(index) - 1);
	}
}
