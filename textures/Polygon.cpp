#include "Polygon.h"
#include <iostream>
#include "PolygonAlgorithm.h"
#include <cmath>

#define INF 10000
using namespace std;

void Polygon::copyFrom(const Polygon& src)
{
	this->points = src.points;
	this->totalPointNumber = src.totalPointNumber;
	this->isUpdated = true;
}

Polygon::Polygon(const Polygon& src) : Shape(src)
{
	this->copyFrom(src);
}

Polygon::Polygon()
{

}

Polygon::Polygon(float * vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber, unsigned int totalVerticeNumber) : Shape(vertices, vertexAttributeNumbers, eachAttributeNumber, totalVerticeNumber)
{
	for (unsigned int i = 0; i < this->totalCoordinateNumber; i += totalVerticeNumber) {
		// local variable point is coopied to points vector and vector allocates memory heap so it remains even after constructor function finishes
		this->points.push_back(Point(vertices[i], vertices[i + 1]));
	}
	this->isUpdated = true;
	this->totalPointNumber = (unsigned) this->points.size();
	this->totalIndiceNumber = 3 * (this->totalPointNumber - 2);
}

Polygon& Polygon::operator=(const Polygon& polygon)
{
	if (this == &polygon) {
		return *this;
	}
	Shape::operator = (polygon);
	copyFrom(polygon);

	return *this;
}

bool Polygon::isIncludePoint(Point point)
{
	// 도형을 선택하는게 도형 움직이는 것보다 덜 자주 일어난다고 가정
   // 그렇기에 isIncludePoint 에서 points 업데이트 하는게 도형 움직일 때마다 points 업데이트 하는 것보다 효율적
	
	glm::vec4 result;
	unsigned int currentIndex = 0;
	int vertexAttributeIndex;

	if (!this->isUpdated) {
		for (int currentIndex = 0; currentIndex < totalPointNumber; currentIndex++) {
			vertexAttributeIndex = currentIndex * this->eachAttributeNumber;

			result = this->matrix * glm::vec4(this->verticeAttributes[vertexAttributeIndex], this->verticeAttributes[vertexAttributeIndex + 1], 0.0, 1.0);
			this->points[currentIndex].x = result.x;
			this->points[currentIndex].y = result.y;
		}
		
		this->isUpdated = true;
	}
	
	return PolygonAlgorithm::isInside(this->points, this->totalPointNumber, point);
}

void Polygon::setShaderValue(Shader* shader)
{
	shader->setVec3("color", color);
	shader->setMat4("transformation", this->matrix);
}

void Polygon::translation(float dx, float dy)
{
	glm::mat4 transMatrix = glm::mat4(1.0f);
	transMatrix[3][0] = dx;
	transMatrix[3][1] = dy;
	this->matrix = transMatrix * this->matrix;
	this->isUpdated = false;
}

void Polygon::scale(float sx, float sy)
{
	cout << sx << "  sx" << sy << " sy " << endl;
	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	
	scaleMatrix[0][0] = 1 + sx;
	scaleMatrix[1][1] = 1 + sy;

	this->matrix = scaleMatrix * this->matrix;
	this->isUpdated = false;
}

void Polygon::rotate(float angle)
{
	glm::mat4 rotationMatrix = glm::mat4(1.0f);
	float cosValue = cos(angle);
	float sinValue = sin(angle);

	rotationMatrix[0][0] = cosValue;
	rotationMatrix[1][0] = -1 * sinValue;
	rotationMatrix[0][1] = sinValue;
	rotationMatrix[1][1] = cosValue;

	this->matrix = rotationMatrix * this->matrix;
	this->isUpdated = false;
}

glm::mat4 Polygon::getMatrix()
{
	return this->matrix;
}

