#include "Polygon.h"
#include <iostream>
#include "PolygonAlgorithm.h"

#define INF 10000
using namespace std;

Polygon::Polygon(float vertices[], vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber, unsigned int totalVerticeNumber)
{
	this->verticeAttributes = vertices;
	this->totalCoordinateNumber = eachAttributeNumber * totalVerticeNumber;
	for (int i = 0; i < this->totalCoordinateNumber; i += totalVerticeNumber) {
		// local variable point is coopied to points vector and vector allocates memory heap so it remains even after constructor function finishes
		this->points.push_back(Point(vertices[i], vertices[i + 1]));
	}

	this->eachAttributeNumber = eachAttributeNumber;
	this->totalVerticeNumber = totalVerticeNumber;
	this->vertexAttributeNumbers = vertexAttributeNumbers;
	this->color = glm::vec3(0, 0, 1);
	//  °íÄ¡±â  
	this->matrix = glm::mat4x4();
	this->initiliazeVertexBufferDatas();
}

void Polygon::initiliazeVertexBufferDatas()
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

Polygon::~Polygon() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

bool Polygon::isIncludePoint(Point point)
{
	cout << "point value  x: " << point.x << "y: " << point.y << endl;
	for (int i = 0; i < 3; i += 1) {
		cout << "triangle point value  x: " << this->points[i].x << "y:" << this->points[i].y << endl;
	}
	
	return PolygonAlgorithm::isInside(this->points, this->totalVerticeNumber, point);
}

void Polygon::setShaderValue(Shader* shader)
{
	shader->setVec3("color", color);
}

Polygon::Polygon()
{

}

void Polygon::render()
{
	//cout << "is this called?"<< endl;
//	cout << this->totalVerticeNumber << endl;
	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, this->totalVerticeNumber);
}
