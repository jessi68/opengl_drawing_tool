#include "Triangle.h"

Triangle::Triangle()
{
	cout << " after hey before h " << endl;
}

// constructor �ϳ� �� �����

Triangle::Triangle(float * vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber)
{	
	
	unsigned int * indices = new unsigned int[3] {
		0, 1, 2
	};

	// �簢�� ����� �Ǹ� �� ���� �Լ� ���� ������ �Ҽ���?
	for (int i = 0; i < 9; i += 3) {
		// local variable point is coopied to points vector and vector allocates memory heap so it remains even after constructor function finishes
		this->points.push_back(Point(vertices[i], vertices[i + 1]));
	}

	this->verticeAttributes = vertices;
	this->indices = indices;
	this->vertexAttributeNumbers = vertexAttributeNumbers;
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

