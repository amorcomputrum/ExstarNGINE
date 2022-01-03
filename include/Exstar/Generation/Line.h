#ifndef EXSTAR_LINE_H
#define EXSTAR_LINE_H

#include "Exstar/Utils/ArrayList.h"

namespace exstar{
	class Line{
	public:
		Line(int width,int minLimitOnY,int maxLimitOnY,int minStepOnX,int maxStepOnX,int minStepOnY,int maxStepOnY,int possibilityOfStep);
		int get(int i);
	private:
		ArrayList<int>* data = new ArrayList<int>();
		void generate(int width,int minLimitOnY,int maxLimitOnY,int minStepOnX,int maxStepOnX,int minStepOnY,int maxStepOnY,int possibilityOfStep);
	};
}
#endif