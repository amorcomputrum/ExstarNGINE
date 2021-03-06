#pragma once

#include "Exstar/Utils/ArrayList.h"
#include "Exstar/Utils/Vector2d.h"

namespace exstar{
	namespace physics{
		class Shape{
		public:
			enum ID{
				AABB,Circle,Polygon
			};
			ID id;
			ArrayList<exstar::Vector2d*>* vertices;
			float r;
			int w,h;
		};
	}
}
