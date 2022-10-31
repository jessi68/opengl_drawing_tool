#ifndef THREE_DIMENSIONAL_FIGURE_H
#define THREE_DIMENSIONAL_FIGURE_H
#include "Polygon.h"
#include "TransformCoordinate.h"
#include "ScaleCoordinate.h"

class ThreeDimensionalFigure: public Shape
{
private:
	void initialize();
	TransformCoordinate* transformCoordinate;
	ScaleCoordinate* scaleCoordinate;
	// downcasting 포인터에서만 working!
	Coordinate* coordinate;
public:
	ThreeDimensionalFigure();
	ThreeDimensionalFigure(float* vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber,  unsigned int totalVerticeNumber);
	ThreeDimensionalFigure(const ThreeDimensionalFigure& src);
	ThreeDimensionalFigure& operator=(const ThreeDimensionalFigure& threeDimensionalFigure);
	// 좋은 아이디어 생각나면 transformation 코드 줄이기
	void changeToScaleMode();
	void changeToTransfomationMode();
	void translation(float dx, float dy, float dz);
	void scale(float svalue, int index);
	void rotate(float angle);
	void renderCoordinate(Shader * shader);
	int isScalingPossible(GLfloat color[3]);
};

#endif