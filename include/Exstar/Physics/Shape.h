#include "Exstar/Utils/ArrayList.h"
#include "Exstar/Utils/Vector2d.h"

namespace exstar{
	class Shape{
	public:
		enum ID{
			AABB,Circle,Polygon
		};
		ID id;
		ArrayList<exstar::Vector2d*>* vertices;
		ArrayList<exstar::Vector2d>* normals;
		float r;
		int w,h;
		void rotate(double radians);
		void calculateNormals();
	};
}