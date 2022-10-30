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

	// 기회되면 const paeamerer 로 바꾸기 vector 같은 경우에는 push back 할 때 constructor 불러옴. 
	// 스터디 때 물어보기 (vector 로 하니까 되네 triangle 생성자 호출되면 렌더링이 안됨) (default constructor 에 아무것도 없는디...)

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
