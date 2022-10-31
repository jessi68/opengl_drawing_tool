#ifndef COORDINATE_H
#define COORDINATE_H

#include "Lines.h"
#include "Polygon.h"

class Coordinate
{
protected:
	Lines lines;
	GLfloat colors[3][3];
	vector<Polygon*> polygons;
	static int COORDINATE_NUMBER;
public:
    void render(Shader * shader);
	Coordinate(GLfloat colors[3][3]);
	Coordinate();
	virtual ~Coordinate();
	int isSameWithOneOfColors(GLfloat color[3]);
};

#endif

