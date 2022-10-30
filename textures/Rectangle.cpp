#include "Rectangle.h"

Rectangle::Rectangle() 
{
	
}

Rectangle::Rectangle(float* vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber) {
	unsigned int* indices = new unsigned int[6] {
		0, 1, 2,
		1, 2, 3
	};

	// �簢�� ����� �Ǹ� �� ���� �Լ� ���� ������ �Ҽ���?
	for (int i = 0; i < 12; i += 3) {
		// local variable point is coopied to points vector and vector allocates memory heap so it remains even after constructor function finishes
		this->points.push_back(Point(vertices[i], vertices[i + 1]));
	}

	this->verticeAttributes = vertices;
	this->indices = indices;
	this->vertexAttributeNumbers = vertexAttributeNumbers;
	this->eachAttributeNumber = eachAttributeNumber;
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
