#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Polygon.h";

class Rectangle : public Polygon
{
public:
	Rectangle();
	Rectangle(float* vertices, vector<unsigned int> vertexAttributeNumbers = { 3 }, unsigned int eachAttributeNumber = 3);
	Rectangle(const Rectangle& src);
	Rectangle& operator=(const Rectangle& rectangle);
};

#endif
