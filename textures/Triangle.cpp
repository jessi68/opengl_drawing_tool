#include "Triangle.h"
#include <stdlib.h>

Triangle::Triangle(float vertices[], vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber) : Shape(vertices, vertexAttributeNumbers, eachAttributeNumber, this->totalVerticeNumber)
{
	this->totalVerticeNumber = 3;
}

Triangle::Triangle() 
{

	//float randomValueX = static_cast <float> (rand()) / static_cast <float> (RAND_MAX  / 1.0);
	//float randomValueY = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 1.0);
	float randomValueX = 0.4;
	float randomValueY = 0.0;
	float vertices[] = {
		// vertex  
		randomValueX - 0.4, randomValueY, 0,
		randomValueX - 0.2, randomValueY + 0.8, 0,
        randomValueX, randomValueY, 0
	};
	this->verticeAttributes = vertices;
	this->vertexAttributeNumbers.push_back(3);
	this->eachAttributeNumber = 3;
	this->totalVerticeNumber = 3;

	this->initiliazeVertexBufferDatas();
}

