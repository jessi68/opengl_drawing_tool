#include "TransformCoordinate.h"

TransformCoordinate::TransformCoordinate(float x, float y, float z)
{
	// new operator 로 생성해도 triangle default 생성자가 호출됨. s
	// bool 변수 (initlizebuffer 할껀지) 이런 생성자 함수 만들어야지. 
	// 생성자 호출 막기 위해 vector 사용

	float* xVertices = new float[9] {
		// vertex  
		x, 0.007, 0,
		x + (float) 0.01, 0.00, 0.005,
		x, -0.007, 0.0
	};
	float* yVertices = new float[9] {
		0, y + (float) 0.016, 0,
		-0.008, y, 0.0,
		0.008, y, 0.0
	};

	float* zVertices = new float[9] {
		0.0, -0.007, z,
		0.0, 0.007, z,
		0.0, 0.0, z + (float) 0.02
	};

	// 기회되면 const paeamerer 로 바꾸기 vector 같은 경우에는 push back 할 때 constructor 불러옴. 
	// 스터디 때 물어보기 (vector 로 하니까 되네 triangle 생성자 호출되면 렌더링이 안됨) (default constructor 에 아무것도 없는디...)
	cout << "trianglee constructor should be called after" << endl;
	this->triangles.push_back(new Triangle(xVertices));
	this->triangles.push_back(new Triangle(yVertices));
	this->triangles.push_back(new Triangle(zVertices));
}

TransformCoordinate::~TransformCoordinate()
{
	
}

void TransformCoordinate::renderHeel()
{
	for (int i = 0; i < 3; i++) {
		triangles[i]->render();
	}
}