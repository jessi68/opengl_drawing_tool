#include "Coordinate.h"

void Coordinate::render() {
	this->lines.render();
	for (int i = 0; i < 3; i++) {
		this->polygons[i]->render();
	}
} 

Coordinate::~Coordinate() {

}