#include "Triangle.h"
#include <glm/glm.hpp>
#include <stdlib.h>

Triangle::Triangle(float vertices[], vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber) : Polygon(vertices, vertexAttributeNumbers, eachAttributeNumber, this->totalVerticeNumber)
{
	this->totalVerticeNumber = 3;
}

Triangle::Triangle() 
{
	float vertices[] = {
		// vertex  
		0.0, 0.0, 0,
		0.2, 0.8, 0,
        0.4, 0.0, 0
	};

	// �簢�� ����� �Ǹ� �� ���� �Լ� ���� ������ �Ҽ���?
	for (int i = 0; i < 9; i += 3) {
		// local variable point is coopied to points vector and vector allocates memory heap so it remains even after constructor function finishes
		this->points.push_back(Point(vertices[i], vertices[i + 1]));
	}

	this->verticeAttributes = vertices;
	this->vertexAttributeNumbers.push_back(3);
	this->eachAttributeNumber = 3;
	this->totalVerticeNumber = 3;
	this->totalCoordinateNumber = eachAttributeNumber * totalVerticeNumber;
	this->color = glm::vec3(0, 0, 1);
	// matrix �ʱ�ȭ
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

