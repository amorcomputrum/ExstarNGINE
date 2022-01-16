#pragma once
#include <cmath>
#include <stdlib.h>
#include "Exstar/Utils/Vector2d.h"
namespace exstar{
	/**
	 * EULER's number as in e
	*/
	const double EULER = 2.71828182845904523536;
	/**
	 * Calculates the distance between 2 objects on a 2d plane
	 * 
	 * @param x1 The first object's x position
	 * @param y1 The first object's y position
	 * @param x2 The second object's x position
	 * @param y2 The second object's y position
	 * 
	 * @return The distance between the 2 objects
	*/
	double Distance(double x1,double y1,double x2, double y2);
	/**
	 * Calculates the distance between 2 objects on a 2d plane
	 * 
	 * @param pos1 The first object's position
	 * @param pos2 The second object's position
	 * 
	 * @return The distance between the 2 objects
	*/
	double Distance(exstar::Vector2d pos1,exstar::Vector2d pos2);
	/**
	 * Returns a Random int in a range
	 * 
	 * @param min The minimum of the range of values to return
	 * @param max The maximum of the range of values to return
	 * 
	 * @return A random number within the min-max range
	*/
	int Random(int min,int max);
}
