#include "TransformCoordinate.h"

TransformCoordinate::TransformCoordinate()
{
	cout << "hey" << endl;
	// new operator �� �����ص� triangle default �����ڰ� ȣ���. 
	// bool ���� (initlizebuffer �Ҳ���) �̷� ������ �Լ� ��������. 
	// ������ ȣ�� ���� ���� vector ���

	float* xVertices = new float[9] {
		// vertex  
		0.20, 0.007, 0,
		0.21, 0.00, 0.005,
		0.20, -0.007, 0.0
	};
	float* yVertices = new float[9] {
		0, 0.216, 0,
		-0.008, 0.2, 0.0,
		0.008, 0.2, 0.0
	};
	float* zVertices = new float[9] {
		0, 0.02, -1.2,
		-0.01, 0.0, -1.3,
		0.0, -0.02, -1.2
	};

	// ��ȸ�Ǹ� const paeamerer �� �ٲٱ� vector ���� ��쿡�� push back �� �� constructor �ҷ���. 
	// ���͵� �� ����� (vector �� �ϴϱ� �ǳ� triangle ������ ȣ��Ǹ� �������� �ȵ�) (default constructor �� �ƹ��͵� ���µ�...)
	cout << "trianglee constructor should be called after" << endl;
	this->triangles.push_back(new Triangle(xVertices));
	this->triangles.push_back(new Triangle(yVertices));
	this->triangles.push_back(new Triangle(zVertices));
}

TransformCoordinate::~TransformCoordinate()
{
	
}

void TransformCoordinate::render()
{
	this->lines.render();

	for (int i = 0; i < 3; i++) {
		triangles[i]->render();
	}
}