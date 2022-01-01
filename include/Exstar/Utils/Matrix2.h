#ifndef EXSTAR_MATRIX2_H
#define EXSTAR_MATRIX2_H
#include "Exstar/Utils/Vector2d.h"
namespace exstar{
	class Matrix2{
	public:
		float m00,m01,m10,m11;
		Matrix2(float m00,float m01,float m10,float m11);
		/**
		 * Create from angle in radian
		 * 
		 * @param radians The radian of the angle
		*/
		void set(float radians);
		/**
		 * Transpose matrix
		 * 
		 * @return transposed matrix
		*/
		exstar::Matrix2 transpose();
		/**
		 * Mulitply 2x2 Matrix by 2x1
		 * 
		 * @param param 2x1 to multiply by
		*/
		exstar::Vector2d operator*(exstar::Vector2d param);
		/**
		 * Mulitply 2x2 Matrix by 2x2
		 * 
		 * @param param 2x2 to multiply by
		*/
		exstar::Matrix2 operator*(exstar::Matrix2 param);
	};
}
#endif