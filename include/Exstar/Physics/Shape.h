#include "Exstar/Utils/ArrayList.h"
#include "Exstar/Utils/Vector2d.h"

namespace exstar{
	class Shape{
	public:
		enum ID{
			Circle,Polygon
		};
		ID id;
		ArrayList<exstar::Vector2d*>* vertices;
		//ArrayList<exstar::Vector2d>* normals;
		int r;
		void rotate(double radians);
		//void calculateNormals();
	};
}