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
	// downcasting �����Ϳ����� working!
	Coordinate* coordinate;
public:
	ThreeDimensionalFigure();
	ThreeDimensionalFigure(float* vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber,  unsigned int totalVerticeNumber);
	ThreeDimensionalFigure(const ThreeDimensionalFigure& src);
	ThreeDimensionalFigure& operator=(const ThreeDimensionalFigure& threeDimensionalFigure);
	// ���� ���̵�� �������� transformation �ڵ� ���̱�
	void changeToScaleMode();
	void changeToTransfomationMode();
	void translation(float dx, float dy, float dz);
	void scale(float svalue, int index);
	void rotate(float angle);
	void transformation(glm::mat3 newMatrix);
	void renderCoordinate(unique_ptr<Shader>& shader);
	void setPosition(float dx, float dy, float dz);
	int isScalingPossible(GLfloat color[3]);
};

#endif