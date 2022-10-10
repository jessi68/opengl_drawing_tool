#include "Polygon.h"

class ThreeDimensionalFigure: Shape
{
public:
	void translation(float dx, float dy, float dz);
	void scale(float sx, float sy, float sz);
	void rotate(float angle);

};

