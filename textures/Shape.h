#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

using namespace std;

class Shape
{
private:
	unsigned int vao;
	unsigned int vbo;
	unsigned int eachAttributeNumber;
	unsigned int totalVerticeNumber;
public:
	Shape(float vertices[], vector<unsigned int> vertextAttributeNumbers, unsigned int eachAttributeNumber, unsigned int totalVerticeNumber);
	~Shape();
	virtual void render();
};

