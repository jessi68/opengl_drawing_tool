#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Point.h"
#include "Shader.h"
#include <glm/glm.hpp>

using namespace std;

class Polygon
{
protected:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int eachAttributeNumber;
	unsigned int totalVerticeNumber; 
	unsigned int totalCoordinateNumber;
	unsigned int totalPointNumber;
	unsigned int totalIndiceNumber;
	float * verticeAttributes;
	unsigned int* indices;
	bool isUpdated;
	glm::vec3 color;
	glm::mat4 matrix;
	vector<Point> points;
	vector<unsigned int> vertexAttributeNumbers;
	void initiliazeVertexBufferDatas();

public:
	Polygon(float* vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber, unsigned int totalVerticeNumber);
	Polygon();
	virtual ~Polygon();
	void copyFrom(const Polygon& src);
	Polygon(const Polygon& src);
	Polygon& operator=(const Polygon& polygon);
	bool isIncludePoint(Point point);
	void setShaderValue(Shader* shader);
	void render();
	// ���߿� movable �� �и��� �ʿ䵵 ������? 
	void translation(float dx, float dy);
	void scale(float sx, float sy);
	void rotate(float angle);
	glm::mat4 getMatrix();

};

