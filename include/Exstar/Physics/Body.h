#include "Exstar/Physics/Shape.h"
#include "Exstar/Utils/Vector2d.h"
#include "Exstar/Physics/TestCollider.h"
namespace exstar{
	class Body{
	public:
		exstar::Shape* shape;
		float restitution;
		int mass;
		float inv_mass;
		exstar::TestCollider testCollider;
		exstar::Vector2d position;
		exstar::Vector2d velocity;
		Body();
		Body(exstar::Vector2d position,float restitution,int mass,exstar::Shape* shape);
		Body(exstar::Vector2d position,exstar::Vector2d velocity,float restitution,int mass,exstar::Shape* shape);
		void Update(double deltaTime);
	};
}
