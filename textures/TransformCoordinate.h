#include "Coordinate.h"
#include "Triangle.h"

class TransformCoordinate : public Coordinate
{
public:
	TransformCoordinate(float x = 0.2, float y = 0.2, float z = 0.6);
	~TransformCoordinate();
};

