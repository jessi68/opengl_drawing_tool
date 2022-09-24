#include "Triangle.h"

Triangle::Triangle(float vertices[], vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber) : Shape(vertices, vertexAttributeNumbers, eachAttributeNumber, this->totalVerticeNumber)
{
	this->totalVerticeNumber = 3;
}

Triangle::Triangle() 
{
	float vertices[] = {
		// vertex  
		-0.4, 0, 0,
		0.0, 0.8, 0,
        0.4, 0, 0
	};
	this->vertices = vertices;
	this->vertexAttributeNumbers.push_back(3);
	this->eachAttributeNumber = 3;
	this->totalVerticeNumber = 3;

	this->initiliazeVertexBufferDatas();
}

