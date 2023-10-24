#ifndef LINES_H
#define LINES_H

#include "Shape.h"

//rectangle 로 그리기
class Lines
{
private:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int eachAttributeNumber;
	unsigned int totalVerticeNumber;
	unsigned int totalCoordinateNumber;
	unsigned int totalIndiceNumber;
	float* verticeAttributes;
	vector<unsigned int> vertexAttributeNumbers;
	unsigned int* indices;
	glm::vec3 color;
	glm::mat4 matrix;
public:
	Lines();
	void initiliazeVertexBufferDatas();
	Lines(float* vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber, unsigned int totalVerticeNumber);
	void copyFrom(const Lines& src);
	Lines(const Lines& src);
	Lines& operator=(const Lines& lines);
	void render(unique_ptr<Shader>& shader);
};

#endif