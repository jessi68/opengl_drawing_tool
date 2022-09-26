#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

using namespace std;

class Shape
{
protected:
	unsigned int vao;
	unsigned int vbo;
	unsigned int eachAttributeNumber;
	unsigned int totalVerticeNumber; 
	float * verticeAttributes;
	vector<pair<float, float>> points;
	vector<unsigned int> vertexAttributeNumbers;
	void initiliazeVertexBufferDatas();
public:
	Shape(float vertices[], vector<unsigned int> vertextAttributeNumbers, unsigned int eachAttributeNumber, unsigned int totalVerticeNumber);
	Shape();
	~Shape();
	bool isInnerPolygon(float x, float y);
	void render();
};

