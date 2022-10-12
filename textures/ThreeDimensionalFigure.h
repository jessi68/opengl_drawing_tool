#ifndef THREE_DIMENSIONAL_FIGURE_H
#define THREE_DIMENSIONAL_FIGURE_H
#include "Polygon.h"

class ThreeDimensionalFigure: public Shape
{
public:
	ThreeDimensionalFigure();
	ThreeDimensionalFigure(float* vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber, unsigned int totalVerticeNumber);
	ThreeDimensionalFigure(const ThreeDimensionalFigure& src);
	ThreeDimensionalFigure& operator=(const ThreeDimensionalFigure& threeDimensionalFigure);
	// ���� ���̵�� �������� transformation �ڵ� ���̱�
	void translation(float dx, float dy, float dz);
	void scale(float sx, float sy, float sz);
	void rotate(float angle);
};

#endif