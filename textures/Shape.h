#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Point.h"

using namespace std;

class Shape
{
protected:
	unsigned int vao;
	unsigned int vbo;
	unsigned int eachAttributeNumber;
	unsigned int totalVerticeNumber; 
	unsigned int totalCoordinateNumber;
	float * verticeAttributes;
	vector<Point> points;
	vector<unsigned int> vertexAttributeNumbers;
	void initiliazeVertexBufferDatas();
public:
	Shape(float vertices[], vector<unsigned int> vertextAttributeNumbers, unsigned int eachAttributeNumber, unsigned int totalVerticeNumber);
	Shape();
	~Shape();
	void render();
};

