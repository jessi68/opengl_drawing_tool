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

	// 사각형 만들게 되면 이 로직 함수 따로 만들어야 할수도?
	for (int i = 0; i < 9; i+= 3) {
		// local variable point is coopied to points vector and vector allocates memory heap so it remains even after constructor function finishes
		this->points.push_back(Point(vertices[i], vertices[i + 1]));
	}

	this->verticeAttributes = vertices;
	this->vertexAttributeNumbers.push_back(3);
	this->eachAttributeNumber = 3;
	this->totalVerticeNumber = 3;
	this->totalCoordinateNumber = eachAttributeNumber * totalVerticeNumber;

	this->initiliazeVertexBufferDatas();
}

