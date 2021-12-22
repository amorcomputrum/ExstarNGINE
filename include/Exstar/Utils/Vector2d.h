#ifndef Vector2d_H
#define Vector2d_H
	namespace exstar{
		class Vector2d{
		public:
			double x,y;
			/**
			 * Initialize The 2dVector
			*/
			Vector2d();
			/**
			 * Initialize The 2dVector
			 * 
			 * @param x Sets the value of x
			 * @param y Sets the value of y
			*/
			Vector2d(double x,double y);
			/** 
			 * Returns the magnitude of the Vector
			 * @return The value of C (a^2 + b^2 = C^2)
			*/
			float magnitude();
			/** 
			 * Returns the square of the magnitude of the Vector
			 * @return The value of C (a^2 + b^2 = C^2)
			*/
			float sqrMagnitude();
			/**
			 * Set the Values of the 2dVector
			 * 
			 * @param x The x value to set the vector to
			 * @param y The y value to set the vector to
			*/
			void set(double x,double y);
			/**
			 * Return the X value of the vector
			 * 
			 * @return the x value of the vector
			*/
			double getX();
			/**
			 * Return the Y value of the vector
			 * 
			 * @return the y value of the vector
			*/
			double getY();
			/**
			 * Adds a Vector2d
			 * 
			 * @param param The Vector to add
			 * 
			 * @returns Result of addition
			 */
			exstar::Vector2d operator+(exstar::Vector2d param);
			/**
			 * Adds a value
			 * 
			 * @param param The value to add
			 * 
			 * @returns Result of addition
			 */
			exstar::Vector2d operator+(double param);
			/**
			 * Adds a Vector2d and saves
			 * 
			 * @param param The Vector to add
			 */
			exstar::Vector2d& operator+=(const exstar::Vector2d& param);
			/**
			 * Adds a Vector2d and saves
			 * 
			 * @param param The Vector to add
			 */
			exstar::Vector2d& operator+=(const double& param);
			/**
			 * Subtracts a Vector2d
			 * 
			 * @param param The Vector to subtract
			 * 
			 * @returns Result of subtraction
			 */
			exstar::Vector2d operator-(exstar::Vector2d param);
			/**
			 * Subtracts a Vector2d
			 * 
			 * @param param The value to subtract
			 * 
			 * @returns Result of subtraction
			 */
			exstar::Vector2d operator-(double param);
			/**
			 * Divides a Vector2d
			 * 
			 * @param param The Vector to divide by
			 * 
			 * @returns Result of division
			 */
			exstar::Vector2d operator/(exstar::Vector2d param);
			/**
			 * Divides a Vector2d
			 * 
			 * @param param The value to divide by
			 * 
			 * @returns Result of division
			 */
			exstar::Vector2d operator/(double param);
			/**
			 * Multiplys a Vector2d
			 * 
			 * @param param The Vector to multiply by
			 * 
			 * @returns Result of multiplication
			 */
			exstar::Vector2d operator*(exstar::Vector2d param);
			/**
			 * Multiplys a Vector2d
			 * 
			 * @param param The value to multiply by
			 * 
			 * @returns Result of multiplication
			 */
			exstar::Vector2d operator*(double param);
			/**
			 * Returns the DotProduct of the 2 vectors
			 * 
			 * @param vec1 The first vector to use
			 * @param vec2 The second vector to use
			 * 
			 * @returns float of the DotProduct
			*/
			static float dot(exstar::Vector2d vec1,exstar::Vector2d vec2);
			/**
			 * Returns the scalar of 2 vectors
			 * 
			 * @param vec1 The first vector
			 * @param vec2 The second vector
			 * 
			 * @returns Returns the scalar of 2 vectors
			*/
			static float cross(exstar::Vector2d vec1,exstar::Vector2d vec2);
			/**
			 * Returns the Vector of a vector and scalar
			 * 
			 * @param vec1 The first vector
			 * @param vec2 The second vector
			 * 
			 * @returns Returns the Vector of a vector and scalar
			*/
			static exstar::Vector2d cross(exstar::Vector2d vec1,float s);
			/**
			 * Returns The Normalized Vector
			 * 
			 * @param vec The Vector to Normalize
			 * 
			 * @returns Normalized Vector
			*/
			static exstar::Vector2d normalize(exstar::Vector2d vec);
		};
	}
	#include "Exstar/Utils/Vector2d.cpp"
#endif