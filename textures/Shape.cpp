#include "Shape.h"
#include <iostream>
#define INF 10000
using namespace std;

Shape::Shape(float vertices[], vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber, unsigned int totalVerticeNumber)
{
	this->verticeAttributes = vertices;
	this->totalCoordinateNumber = eachAttributeNumber * totalVerticeNumber;
	/*for (int i = 0; i < this->totalCoordinateNumber; i += totalVerticeNumber) {
		// local variable point is coopied to points vector and vector allocates memory heap so it remains even after constructor function finishes
		this->points.push_back(Point(vertices[i], vertices[i + 1]));
	}*/

	this->eachAttributeNumber = eachAttributeNumber;
	this->totalVerticeNumber = totalVerticeNumber;
	this->vertexAttributeNumbers = vertexAttributeNumbers;
	this->initiliazeVertexBufferDatas();
}

void Shape::initiliazeVertexBufferDatas()
{

	glGenVertexArrays(1, &(this->vao));
	glGenBuffers(1, &(this->vbo));

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->totalCoordinateNumber, verticeAttributes, GL_STATIC_DRAW);

	glBindVertexArray(this->vao);

	int index = 0;
	int eachAttributeSize = eachAttributeNumber * sizeof(float);
	int startValue = 0;

	for (auto vertexAttributeNumber : vertexAttributeNumbers) {
		glVertexAttribPointer(index, vertexAttributeNumber, GL_FLOAT, GL_FALSE, eachAttributeSize, (void*)(startValue * sizeof(float)));
		glEnableVertexAttribArray(index);
		startValue += vertexAttributeNumber;
		index += 1;
	}

}

Shape::~Shape() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

Shape::Shape()
{

}

void Shape::render()
{
	//cout << "is this called?"<< endl;
//	cout << this->totalVerticeNumber << endl;
	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, this->totalVerticeNumber);
}
