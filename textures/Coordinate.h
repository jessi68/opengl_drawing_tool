#ifndef COORDINATE_H
#define COORDINATE_H

#include "Lines.h"
#include "Polygon.h"

class Coordinate
{
protected:
	Lines lines;
	vector<Polygon*> polygons;
	virtual void renderHeel() = 0;
public:
    void render();
	virtual ~Coordinate();
};

#endif
