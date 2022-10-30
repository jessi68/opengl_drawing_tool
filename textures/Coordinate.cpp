#include "Coordinate.h"

void Coordinate::render() {
	this->renderHeel();
	this->lines.render();
}

Coordinate::~Coordinate() {

}