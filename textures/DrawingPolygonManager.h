//#include "Shape.h"
#include <vector>
#include "Triangle.h"

using namespace std;

// sigleton
class DrawingPolygonManager
{
private:
	static DrawingPolygonManager* drawingManager;
	DrawingPolygonManager();
	vector<Shape> polygonsToRender;
	static void Destroy();
public:
	/**
	* Singletons should not be cloneable.
	* =delete: prohibiting copying
	*/
	static DrawingPolygonManager* getInstance();
	DrawingPolygonManager(DrawingPolygonManager& other) = delete;
	void operator= (const DrawingPolygonManager &) = delete;
	void addPolygon(const Shape & shape);
	void renderAll();
};

//

