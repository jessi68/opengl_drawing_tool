#include "Polygon.h"

class Triangle: public Polygon
{
public:
	Triangle(float vertices[], vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber);
	Triangle();
	Triangle& operator=(const Triangle& triangle);
};

