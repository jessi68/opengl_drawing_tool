#include "Coordinate.h"
#include "Rectangle.h"

class ScaleCoordinate : public Coordinate
{
private:
	vector<Rectangle*> rectangles;
protected:
	void renderHeel();
public:
	ScaleCoordinate(float x = 0.2, float y = 0.2, float z = 0.6);
	~ScaleCoordinate();
};

