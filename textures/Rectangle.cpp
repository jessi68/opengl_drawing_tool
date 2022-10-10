#include "Rectangle.h"

Rectangle::Rectangle(float* vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber) : Polygon(vertices, vertexAttributeNumbers, eachAttributeNumber, this->totalVerticeNumber)
{
	unsigned int* indices = new unsigned int[6] {
		0, 1, 2,
		1, 2, 3
	};

	this->indices = indices;
	this->totalVerticeNumber = 4;
}

Rectangle::Rectangle() {
	
	float* vertices = new float[12] {
		// vertex  
		-0.2, 0.0, 0,
		-0.2, 0.4, 0,
		0.2, 0.0, 0,
		0.2, 0.4, 0,
	};

	unsigned int* indices = new unsigned int[6] {
		0, 1, 2,
		1, 2, 3
	};

	// 사각형 만들게 되면 이 로직 함수 따로 만들어야 할수도?
	for (int i = 0; i < 12; i += 3) {
		// local variable point is coopied to points vector and vector allocates memory heap so it remains even after constructor function finishes
		this->points.push_back(Point(vertices[i], vertices[i + 1]));
	}

	this->verticeAttributes = vertices;
	this->indices = indices;
	this->vertexAttributeNumbers.push_back(3);
	this->eachAttributeNumber = 3;
	this->totalVerticeNumber = 4;
	this->totalPointNumber = 4;
	this->totalIndiceNumber = 3 * (this->totalPointNumber - 2);
	this->totalCoordinateNumber = eachAttributeNumber * totalVerticeNumber;
	this->color = glm::vec3(0, 1, 0);
	this->matrix = glm::mat4(1.0f);
	this->isUpdated = true;

	this->initiliazeVertexBufferDatas();
}



Rectangle::Rectangle(const Rectangle& src) : Polygon(src)
{

}

Rectangle& Rectangle::operator=(const Rectangle& rectangle)
{
	Polygon::operator=(rectangle);
	return *this;
}
