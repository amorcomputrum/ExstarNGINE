#ifndef EXSTAR_ENGINE_H
#define EXSTAR_ENGINE_H
#include "Exstar/Utils/ArrayList.h"
#include "Exstar/Physics/PCollision.h"
namespace exstar{
	class Engine{
	public:
		ArrayList<exstar::Body*>* bodies = new ArrayList<exstar::Body*>();;
		exstar::PCollision collision;
		Engine();
		void add(exstar::Body* body);
		exstar::Body* getById(std::string id);
		void Update(double deltaTime);
		static void HandleCollision(exstar::PCollision* collision);
		static void Impulse(exstar::PCollision* collision);
		static void PositionalCorrection(exstar::PCollision* collision);
	};
}
#endif