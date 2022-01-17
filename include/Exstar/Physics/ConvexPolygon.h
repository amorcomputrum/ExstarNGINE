#pragma once

#include "Exstar/Graphics/Shape.h"
#include "Exstar/Physics/Shape.h"
#include "Exstar/Utils/Point.h"

namespace exstar{
	namespace physics{
		class ConvexPolygon : public exstar::physics::Shape{
		public:
			ConvexPolygon();
			ConvexPolygon(exstar::Shape shape);
			void add(unsigned int x, unsigned int y);
			void add(exstar::Vector2d vertex);
			void add(exstar::Point vertex);
			void remove(unsigned int x, unsigned int y);
			void remove(exstar::Vector2d vertex);
			void remove(exstar::Point vertex);
			void remove(int i);
			int getSize();
			exstar::Vector2d getVertex(int i);
		private:
			int getIndex(unsigned int x, unsigned int y);
		};
	}
}
