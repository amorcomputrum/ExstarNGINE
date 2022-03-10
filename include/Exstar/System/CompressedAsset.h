#pragma once

#include "Exstar/System/File.h"

namespace exstar{
	class CompressedAsset : public exstar::File{
	public:
		CompressedAsset(std::string file) : exstar::File(file){

		}

	};
}