#include "Polygon.h";

class Rectangle : public Polygon
{
public:
	Rectangle(float* vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber);
	Rectangle();
	Rectangle(const Rectangle& src);
	Rectangle& operator=(const Rectangle& rectangle);
};

