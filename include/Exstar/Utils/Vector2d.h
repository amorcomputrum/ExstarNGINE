#ifndef Vector2d_H
#define Vector2d_H
	namespace exstar{
		class Vector2d{
		public:
			/**
			 * Initialize The 2dVector
			 * 
			 * @param x Sets the value of x
			 * @param y Sets the value of y
			*/
			Vector2d(int x,int y);
			/**
			 * Returns the dot product of 2 vectors
			 * 
			 * @param v Other vector to use when calculating dot
			 * 
			 * The dot product of two vectors is equal to the product of the magnitude of the two vectors and the cosecant of the angle between the two vectors
			*/
			float dot(exstar::Vector2d v);
			/** 
			 * Returns the magnitude of the Vector
			 * @return The value of C (a^2 + b^2 = C^2)
			*/
			float magnitude();
			/**
			 * Adds a vector to this vector
			 * 
			 * @param vec The vector to add to this vector
			*/
			void add(exstar::Vector2d vec);
			/**
			 * Adds a vector to this vector
			 * 
			 * @param x The x value to add
			 * @param y The y value to add
			*/
			void add(int x,int y);
			/**
			 * Subtracts a vector to this vector
			 * 
			 * @param vec The vector to subtract to this vector
			*/
			void min(exstar::Vector2d vec);
			/**
			 * Subtracts a vector to this vector
			 * 
			 * @param x The x value to subtract
			 * @param y The y value to subtract
			*/
			void min(int x,int y);
			/**
			 * Multipies a vector to this vector
			 * 
			 * @param vec The vector to multipy to this vector
			*/
			void mul(exstar::Vector2d vec);
			/**
			 * Multiplies a vector to this vector
			 * 
			 * @param x The x value to multipy
			 * @param y The y value to multipy
			*/
			void mul(int x,int y);
			/**
			 * Divides a vector to this vector
			 * 
			 * @param vec The vector to divide to this vector
			*/
			void div(exstar::Vector2d vec);
			/**
			 * Divides a vector to this vector
			 * 
			 * @param x The x value to divide
			 * @param y The y value to divide
			*/
			void div(int x,int y);
			/**
			 * Set the Values of the 2dVector
			 * 
			 * @param x The x value to set the vector to
			 * @param y The y value to set the vector to
			*/
			void set(int x,int y);
			/**
			 * Return the X value of the vector
			 * 
			 * @return the x value of the vector
			*/
			int getX();
			/**
			 * Return the Y value of the vector
			 * 
			 * @return the y value of the vector
			*/
			int getY();
		private:
			/**
			 * The X and Y values of the vector
			 * data[0] = x
			 * data[1] = y
			*/
			int data [2];
		};
	}
#endif