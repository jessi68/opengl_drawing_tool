#ifndef COORDINATE_H
#define COORDINATE_H

#include "Lines.h"
#include "Polygon.h"

class Coordinate
{
protected:
	Lines lines;
	int colors[3][3];
	vector<Polygon*> polygons;
public:
    void render(Shader * shader);
	Coordinate();
	virtual ~Coordinate();
};

#endif

