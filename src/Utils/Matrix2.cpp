#include "Exstar/Utils/Math.h"

#include "Exstar/Utils/Matrix2.h"

exstar::Matrix2::Matrix2(float m00, float m01, float m10, float m11){
	this->m00 = m00;
	this->m01 = m01;
	this->m10 = m10;
	this->m11 = m11;
}

void exstar::Matrix2::set(float radians){
	float c = cos(radians);
	float s = sin(radians);

	m00 = c ;
	m01 = -s;
	m10 = s ;
	m11 = c ;
}

exstar::Matrix2 exstar::Matrix2::transpose(){
	return exstar::Matrix2(m00, m10, m01, m11);
}

exstar::Vector2d exstar::Matrix2::operator*(exstar::Vector2d param){
	return exstar::Vector2d(m00*param.x + m01*param.y, m10*param.x + m11*param.y);
}

exstar::Matrix2 exstar::Matrix2::operator*(exstar::Matrix2 param){
	return exstar::Matrix2(m00*param.m00 + m01*param.m10, m00*param.m01*param.m01 + m01*param.m11,
						   m10*param.m00 + m11*param.m10, m10*param.m01 + m11*param.m11);
}
