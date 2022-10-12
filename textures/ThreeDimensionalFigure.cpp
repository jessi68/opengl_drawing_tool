#include "ThreeDimensionalFigure.h"

ThreeDimensionalFigure::ThreeDimensionalFigure()
{
}

ThreeDimensionalFigure::ThreeDimensionalFigure(float* vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber, unsigned int totalVerticeNumber) : Shape(vertices, vertexAttributeNumbers, eachAttributeNumber, totalVerticeNumber)
{

}

ThreeDimensionalFigure::ThreeDimensionalFigure(const ThreeDimensionalFigure& src) : Shape(src)
{

}

ThreeDimensionalFigure& ThreeDimensionalFigure::operator=(const ThreeDimensionalFigure& threeDimensionalFigure)
{
	Shape::operator=(threeDimensionalFigure);
	return *this;
}

void ThreeDimensionalFigure::translation(float dx, float dy, float dz)
{
	glm::mat4 transMatrix = glm::mat4(1.0f);
	transMatrix[3][0] = dx;
	transMatrix[3][1] = dy;
	transMatrix[3][2] = dz;

	this->matrix = transMatrix * this->matrix;
}

void ThreeDimensionalFigure::scale(float sx, float sy, float sz)
{
	glm::mat4 scaleMatrix = glm::mat4(1.0f);

	scaleMatrix[0][0] = 1 + sx;
	scaleMatrix[1][1] = 1 + sy;
	scaleMatrix[2][2] = 1 + sz;

	this->matrix = scaleMatrix * this->matrix;
}

void ThreeDimensionalFigure::rotate(float angle)
{
	glm::mat4 rotationMatrix = glm::mat4(1.0f);
	float cosValue = cos(angle);
	float sinValue = sin(angle);

	rotationMatrix[0][0] = cosValue;
	rotationMatrix[1][0] = -1 * sinValue;
	rotationMatrix[0][1] = sinValue;
	rotationMatrix[1][1] = cosValue;

	this->matrix = rotationMatrix * this->matrix;
}
