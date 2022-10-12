#include "Cube.h"

Cube::Cube(float* vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber, unsigned int * indices) : ThreeDimensionalFigure(vertices, vertexAttributeNumbers, eachAttributeNumber, 8) {
	this->indices = indices;
}

Cube::Cube() {
	float* vertices = new float[24] {
		-0.1f, 0.1f, -0.1f, //Point A 0
		-0.1f, 0.1f, 0.1f,//Point B 1
		0.1f, 0.1f, -0.1f,//Point C 2
		0.1f, 0.1f, 0.1f, //Point D 3
		-0.1f, -0.1f, -0.1f, //Point E 4
		-0.1f, -0.1f, 0.1f,//Point F 5
		0.1f, -0.1f, -0.1f,//Point G 6
		0.1f, -0.1f, 0.1f//Point H 7
	};

	unsigned int* indices = new unsigned int[36] {
		/*Above ABC,BCD*/
		0, 1, 2,
		1, 2, 3,
        /*Following EFG,FGH*/
		4, 5, 6,
		5, 6, 7,
		/*Left ABF,AEF*/
		0, 1, 5,
		0, 4, 5,
		/*Right side CDH,CGH*/
		2, 3, 7,
		2, 6, 7,
		/*ACG,AEG*/
		0, 2, 6,
		0, 4, 6,
		/*Behind BFH,BDH*/
		1, 5, 7,
		1, 3, 7
	};

	this->verticeAttributes = vertices;
	this->indices = indices;
	this->vertexAttributeNumbers.push_back(3);
	this->eachAttributeNumber = 3;
	this->totalVerticeNumber = 8;
	this->totalIndiceNumber = 36;
	this->totalCoordinateNumber = eachAttributeNumber * totalVerticeNumber;
	this->color = glm::vec3(0, 1, 0);
	this->matrix = glm::mat4(1.0f);

	this->initiliazeVertexBufferDatas();
}

Cube& Cube::operator=(const Cube& cube)
{
	ThreeDimensionalFigure::operator=(cube);
	return *this;
}


Cube::Cube(const Cube& src) : ThreeDimensionalFigure(src)
{

}