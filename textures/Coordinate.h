#ifndef COORDINATE_H
#define COORDINATE_H

#include "Lines.h"

class Coordinate
{
protected:
	Lines lines;
	virtual void renderHeel() = 0;
public:
    void render();
	virtual ~Coordinate();
};

#endif
