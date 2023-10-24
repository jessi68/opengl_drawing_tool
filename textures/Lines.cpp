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

void Lines::initiliazeVertexBufferDatas()
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

Lines::Lines(float* vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber, unsigned int totalVerticeNumber)
{
	this->verticeAttributes = vertices;
	this->eachAttributeNumber = eachAttributeNumber;
	this->totalVerticeNumber = totalVerticeNumber;
	this->totalCoordinateNumber = eachAttributeNumber * totalVerticeNumber;
	this->vertexAttributeNumbers = vertexAttributeNumbers;
	this->totalIndiceNumber = 3 * (this->totalVerticeNumber - 2);
	this->indices = new unsigned int[totalIndiceNumber];
	for (int i = 0; i < totalIndiceNumber; i++) {
		this->indices[i] = i;
	}

	unsigned int* indices = new unsigned int[3] {
		0, 1, 2
	};

	this->indices = indices;
	this->color = glm::vec3(0, 0, 1);
	this->matrix = glm::mat4(1.0f);
	this->initiliazeVertexBufferDatas();
}

void Lines::copyFrom(const Lines& src)
{

}

Lines::Lines(const Lines& src)
{
}

Lines& Lines::operator=(const Lines& lines)
{
	if (this == &lines) {
		return *this;
	}

	copyFrom(lines);
}

void Lines::render(unique_ptr<Shader>& shader) {
	glBindVertexArray(this->vao);
	glDrawElements(GL_LINES, this->totalIndiceNumber, GL_UNSIGNED_INT, 0);
}