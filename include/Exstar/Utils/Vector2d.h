#ifndef Vector2d_H
#define Vector2d_H
	namespace exstar{
		class Vector2d{
		public:
			double x,y;
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

			exstar::Vector2d operator+(exstar::Vector2d param);
			exstar::Vector2d operator+(double param);
			exstar::Vector2d operator-(exstar::Vector2d param);
			exstar::Vector2d operator-(double param);
			exstar::Vector2d operator/(exstar::Vector2d param);
			exstar::Vector2d operator/(double param);
			exstar::Vector2d operator*(exstar::Vector2d param);
			exstar::Vector2d operator*(double param);

			static float dot(exstar::Vector2d vec1,exstar::Vector2d vec2);
		};
	}
#endif