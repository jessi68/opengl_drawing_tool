#include "Shape.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Shape::initiliazeVertexBufferDatas()
{
	glGenVertexArrays(1, &(this->vao));
	glGenBuffers(1, &(this->vbo));
	glGenBuffers(1, &(this->ebo));

	glBindVertexArray(this->vao);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->totalCoordinateNumber, verticeAttributes, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * this->totalIndiceNumber, indices, GL_STATIC_DRAW);

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

Shape::Shape(float* vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber, unsigned int totalVerticeNumber)
{
	this->verticeAttributes = vertices;
	this->totalCoordinateNumber = eachAttributeNumber * totalVerticeNumber;
	
	this->eachAttributeNumber = eachAttributeNumber;
	this->totalVerticeNumber = totalVerticeNumber;
	this->vertexAttributeNumbers = vertexAttributeNumbers;
	this->color = glm::vec3(0, 0, 1);
	//  °íÄ¡±â  
	this->matrix = glm::mat4(1.0f);
	this->initiliazeVertexBufferDatas();
}

Shape::~Shape()
{
	delete[] this->verticeAttributes;
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	delete[] this->indices;
}

void Shape::copyFrom(const Shape& src)
{
	this->verticeAttributes = src.verticeAttributes;
	this->totalCoordinateNumber = src.totalCoordinateNumber;
	this->eachAttributeNumber = src.eachAttributeNumber;
	this->totalVerticeNumber = src.totalVerticeNumber;
	this->vertexAttributeNumbers = src.vertexAttributeNumbers;
	this->color = src.color;
	this->matrix = src.matrix;
	this->indices = src.indices;
}

Shape::Shape(const Shape& src)
{
	this->copyFrom(src);
}

Shape& Shape::operator=(const Shape& shape)
{
	if (this == &shape) {
		return *this;
	}
	copyFrom(shape);

	return *this;
}

void Shape::render()
{
	glBindVertexArray(this->vao);
	glDrawElements(GL_TRIANGLES, this->totalIndiceNumber, GL_UNSIGNED_INT, 0);
}

