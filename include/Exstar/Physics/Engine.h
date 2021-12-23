#include "Exstar/Utils/ArrayList.h"
#include "Exstar/Physics/PCollision.h"
namespace exstar{
	class Engine{
	public:
		ArrayList<exstar::Body>* bodies = new ArrayList<exstar::Body>;
		Engine();
		void Update(double deltaTime);
		void Impulse(exstar::PCollision collision);
		void PositionalCorrection(exstar::PCollision collision);
	};
}