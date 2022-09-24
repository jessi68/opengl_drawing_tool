#include "Shape.h"

class Triangle: public Shape
{
public:
	Triangle(float vertices[], vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber);
	Triangle();
	//virtual void render();
};

