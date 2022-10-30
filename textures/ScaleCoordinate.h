#include "Coordinate.h"
#include "Rectangle.h"

class ScaleCoordinate : public Coordinate
{

public:
	ScaleCoordinate(float x = 0.2, float y = 0.2, float z = 0.6);
	~ScaleCoordinate();
};

