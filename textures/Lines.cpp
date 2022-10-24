#include "Lines.h"

Lines::Lines()
{
	float* vertices = new float[12] {
		// vertex  
		0.00, 0.0, 0.00,
		0.20, 0.00, 0,
		0, 0.00, 0.6,
		0, 0.2, 0
	};

	unsigned int* indices = new unsigned int[6] {
		0, 1, 
	    0, 2,
	    0, 3
	};

	this->verticeAttributes = vertices;
	this->indices = indices;
	this->vertexAttributeNumbers.push_back(3);
	this->eachAttributeNumber = 3;
	this->totalVerticeNumber = 4;
	this->totalCoordinateNumber = eachAttributeNumber * totalVerticeNumber;
	this->color = glm::vec3(0, 0, 1);
	this->matrix = glm::mat4(1.0f);
	this->totalIndiceNumber = 6;
	this->initiliazeVertexBufferDatas();
}

Lines::Lines(float* vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber, unsigned int totalVerticeNumber) : Shape(vertices, vertexAttributeNumbers, eachAttributeNumber, totalVerticeNumber)
{

}

void Lines::copyFrom(const Lines& src)
{

}

Lines::Lines(const Lines& src) : Shape(src)
{
}

Lines& Lines::operator=(const Lines& lines)
{
	if (this == &lines) {
		return *this;
	}
	Shape::operator = (lines);
	copyFrom(lines);
}

void Lines::render() {
	glBindVertexArray(this->vao);
	glDrawElements(GL_LINES, this->totalIndiceNumber, GL_UNSIGNED_INT, 0);
}