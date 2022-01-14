#pragma once

#include "Exstar/Utils/Point.h"
#include "Exstar/Utils/Vector2d.h"
#include "Exstar/Utils/ArrayList.h"

namespace exstar{
	class Shape{
	public:
		Shape();
		void add(unsigned int x,unsigned int y);
		void add(exstar::Vector2d vertex);
		void add(exstar::Point vertex);
		void remove(unsigned int x,unsigned int y);
		void remove(exstar::Vector2d vertex);
		void remove(exstar::Point vertex);
		void remove(int i);
		exstar::Vector2d getVector(int i);
		exstar::Point getPoint(int i);
		unsigned int getX(int i);
		unsigned int getY(int i);
		unsigned int* getVAO();
		int getSize();
	private:
		exstar::ArrayList<exstar::Point>* vertices = new exstar::ArrayList<exstar::Point>;
		unsigned int VAO,VBO;
		int getIndex();
		void loadShader();
	};
}