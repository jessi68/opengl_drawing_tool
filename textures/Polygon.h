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
	unsigned int eachAttributeNumber;
	unsigned int totalVerticeNumber; 
	unsigned int totalCoordinateNumber;
	float * verticeAttributes;
	glm::vec3 color;
	glm::mat4 matrix;
	vector<Point> points;
	vector<unsigned int> vertexAttributeNumbers;
	void initiliazeVertexBufferDatas();

public:
	Polygon(float vertices[], vector<unsigned int> vertextAttributeNumbers, unsigned int eachAttributeNumber, unsigned int totalVerticeNumber);
	Polygon();
	virtual ~Polygon();
	bool isIncludePoint(Point point);
	void setShaderValue(Shader* shader);
	void render();
};

