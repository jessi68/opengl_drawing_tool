#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Point.h"
#include "Shape.h"
#include <glm/glm.hpp>

using namespace std;

// 2d shape like triangle and rectangle
class Polygon : public Shape
{
protected:
	bool isUpdated;
	vector<Point> points;
	unsigned int totalPointNumber;
public:
	Polygon();
	Polygon(float* vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber, unsigned int totalVerticeNumber);
	void copyFrom(const Polygon& src);
	Polygon(const Polygon& src);
	Polygon& operator=(const Polygon& polygon);
	bool isIncludePoint(Point point);
	void translation(float dx, float dy);
	void scale(float sx, float sy);
	void rotate(float angle);
	glm::mat4 getMatrix();
};

