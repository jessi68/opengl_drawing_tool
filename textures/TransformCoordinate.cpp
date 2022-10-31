#include "TransformCoordinate.h"

TransformCoordinate::TransformCoordinate(float x, float y, float z)
{
	// new operator �� �����ص� triangle default �����ڰ� ȣ���. s
	// bool ���� (initlizebuffer �Ҳ���) �̷� ������ �Լ� ��������. 
	// ������ ȣ�� ���� ���� vector ���

	float* xVertices = new float[9] {
		// vertex  
		x, 0.014, 0,
		x + (float) 0.02, 0.00, 0.01,
		x, -0.014, 0.0
	};
	float* yVertices = new float[9] {
		0, y + (float) 0.032, 0,
		-0.016, y, 0.0,
		0.016, y, 0.0
	};

	float* zVertices = new float[9] {
		0.0, -0.007, z,
		0.0, 0.007, z,
		0.0, 0.0, z + (float) 0.02
	};

	// ��ȸ�Ǹ� const paeamerer �� �ٲٱ� vector ���� ��쿡�� push back �� �� constructor �ҷ���. 
	// ���͵� �� ����� (vector �� �ϴϱ� �ǳ� triangle ������ ȣ��Ǹ� �������� �ȵ�) (default constructor �� �ƹ��͵� ���µ�...)
	cout << "trianglee constructor should be called after" << endl;
	this->polygons.push_back(new Triangle(xVertices));
	this->polygons.push_back(new Triangle(yVertices));
	this->polygons.push_back(new Triangle(zVertices));
}

TransformCoordinate::~TransformCoordinate()
{
	
}
