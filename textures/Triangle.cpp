#include "Triangle.h"

Triangle::Triangle(float * vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber) : Polygon(vertices, vertexAttributeNumbers, eachAttributeNumber, this->totalVerticeNumber)
{
	unsigned int* indices = new unsigned int[3] {
		0, 1, 2
	};
	this->totalVerticeNumber = 3;
	this->indices = indices;
}

Triangle::Triangle() 
{
	float * vertices = new float[9] {
		// vertex  
		-0.2, 0.0, 0,
		0, 0.4, 0,
		0.2, 0.0, 0
	};

	unsigned int * indices = new unsigned int[3] {
		0, 1, 2
	};

	// 사각형 만들게 되면 이 로직 함수 따로 만들어야 할수도?
	for (int i = 0; i < 9; i += 3) {
		// local variable point is coopied to points vector and vector allocates memory heap so it remains even after constructor function finishes
		this->points.push_back(Point(vertices[i], vertices[i + 1]));
	}

	this->verticeAttributes = vertices;
	this->indices = indices;
	this->vertexAttributeNumbers.push_back(3);
	this->eachAttributeNumber = 3;
	this->totalVerticeNumber = 3;
	this->totalCoordinateNumber = eachAttributeNumber * totalVerticeNumber;
	this->color = glm::vec3(0, 0, 1);
	this->matrix = glm::mat4(1.0f);
	this->isUpdated = true;
	this->totalPointNumber = 3;
	this->totalIndiceNumber = 3 * (this->totalPointNumber - 2);
	this->initiliazeVertexBufferDatas();
}

Triangle::Triangle(const Triangle& src) : Polygon(src)
{
	
}

Triangle& Triangle::operator=(const Triangle& triangle)
{
	Polygon::operator=(triangle);
	return *this;
}

