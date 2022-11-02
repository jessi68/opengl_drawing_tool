#include "Coordinate.h"

Coordinate::Coordinate() : colors{ {1.0, 0, 0}, {0, 1.0, 0}, {0, 0, 1.0} } {

}

Coordinate::Coordinate(GLfloat colors[3][3]) {
	for (int i = 0; i < Coordinate::COORDINATE_NUMBER; i++) {
		for (int j = 0; j < 3; j++) {
			this->colors[i][j] = colors[i][j];
		}
	}
}

void Coordinate::render(Shader * shader) {
	this->lines.render();
	
	for (int i = 0; i < Coordinate::COORDINATE_NUMBER; i++) {
		shader->setVec3("color", colors[i][0], colors[i][1], colors[i][2]);
		this->polygons[i]->render();
	}
} 

Coordinate::~Coordinate() {

}

int Coordinate::isSameWithOneOfColors(GLfloat color[3]) {
	bool isSame;
	GLfloat interval;

	for (int i = 0; i < Coordinate::COORDINATE_NUMBER; i++) {
		isSame = true;
		for (int j = 0; j < 3; j++) {
			interval = colors[i][j] - color[j];

			if (!(interval < 0.008 && interval > -0.008)) {
				isSame = false;
				break;
			}
		}

		if (isSame == true) {
			return i;
		}
	}

	return -1;
}

int Coordinate::COORDINATE_NUMBER = 3;