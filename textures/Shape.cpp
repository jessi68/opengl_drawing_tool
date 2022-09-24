#include "Shape.h"
#include <iostream>
using namespace std;

Shape::Shape(float vertices[], vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber, unsigned int totalVerticeNumber)
{
	this->vertices = vertices;
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * eachAttributeNumber * totalVerticeNumber, vertices, GL_STATIC_DRAW);

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



Shape::Shape()
{

}

Shape::~Shape() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	cout << "is it called?";
}

void Shape::render()
{
	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, this->totalVerticeNumber);
}
