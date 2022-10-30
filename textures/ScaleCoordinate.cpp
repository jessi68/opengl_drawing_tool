#include "ScaleCoordinate.h"

ScaleCoordinate::ScaleCoordinate(float x, float y, float z)
{
	float* xVertices = new float[12] {
		// vertex  
		x + (float) 0.01, 0.007, 0,
		x + (float)0.01, -0.007, 0,
		x, 0.007, 0,
		x, -0.007, 0.0
	};

	float* yVertices = new float[12] {
		-0.008, y, 0.0,
	    -0.008, y + (float)0.016, 0,
		0.008, y, 0.0,
	    0.008, y + (float)0.016, 0
	};

	float* zVertices = new float[12] {
		0.0, 0.007, z,
		0.0, -0.007, z,
		0.0, 0.007, z + (float)0.02,
		0.0, -0.007, z + (float) 0.02
 	};

	// ��ȸ�Ǹ� const paeamerer �� �ٲٱ� vector ���� ��쿡�� push back �� �� constructor �ҷ���. 
	// ���͵� �� ����� (vector �� �ϴϱ� �ǳ� triangle ������ ȣ��Ǹ� �������� �ȵ�) (default constructor �� �ƹ��͵� ���µ�...)

	this->rectangles.push_back(new Rectangle(xVertices));
	this->rectangles.push_back(new Rectangle(yVertices));
	this->rectangles.push_back(new Rectangle(zVertices));
}

ScaleCoordinate::~ScaleCoordinate()
{
}

void ScaleCoordinate::renderHeel()
{
	for (int i = 0; i < 3; i++) {
		this->rectangles[i]->render();
	}

}
