#include "Coordinate.h"
#include "Lines.h"
#include "Triangle.h"

class TransformCoordinate : public Coordinate
{
private:
	Lines lines;
	vector<Triangle*> triangles;
public:
	TransformCoordinate(float x = 0.2, float y = 0.2, float z = 0.6);
	~TransformCoordinate();
	void render();
};

