#include "Coordinate.h"
#include "Lines.h"
#include "Triangle.h"

class TransformCoordinate : public Coordinate
{
private:
	Lines lines;
	vector<Triangle*> triangles;
public:
	TransformCoordinate();
	~TransformCoordinate();
	void render();
};

