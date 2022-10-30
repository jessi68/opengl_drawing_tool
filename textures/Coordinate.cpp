#include "Coordinate.h"

Coordinate::Coordinate() : colors{ {1, 0, 0}, {0, 1, 0}, {0, 0, 1} } {

}

void Coordinate::render(Shader * shader) {
	this->lines.render();
	for (int i = 0; i < 3; i++) {
		shader->setVec3("color", colors[i][0], colors[i][1], colors[i][2]);
		this->polygons[i]->render();
	}
} 

Coordinate::~Coordinate() {

}