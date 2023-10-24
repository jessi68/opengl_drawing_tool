#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Polygon.h"

class Triangle: public Polygon
{
public:
	Triangle();
	Triangle(float * vertices, vector<unsigned int> vertexAttributeNumbers = { 3}, unsigned int eachAttributeNumber = 3);
	Triangle(const Triangle& src);
	Triangle& operator=(const Triangle& triangle);
};

#endif

