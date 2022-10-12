#include "ThreeDimensionalFigure.h"
#

class Cube : public ThreeDimensionalFigure
{
public:
	Cube(float* vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber, unsigned int* indices, glm::vec3 center);
	Cube();
	Cube(const Cube& src);
	Cube& operator=(const Cube& cube);
private: 
	glm::vec3 center;
};

