
#include <vector>
#include "Triangle.h"
#include "Dimension.h"
#include "ThreeDimensionalFigure.h"

using namespace std;

class ShapeManager
{
private:
	static ShapeManager* drawingManager;
	DIMENSION dimension = TWO;
	ShapeManager();
	vector<Polygon*> polygons;
	vector<ThreeDimensionalFigure*> threeDimensionFigures;
	vector<Polygon*> countourPolygons;
	// 객체 두번 생성하는 거 막으려고 포인터로 함
	Shader* basicShader;
	int polygonNumber;
	int threeDimensionalFigureNumber;
	int selectedPolygonIndex;
	int selectedThreeDimensionalFigureIndex;
	static void Destroy();
public:
	/**
	* Singletons should not be cloneable.
	* =delete: prohibiting copying
	*/
	static ShapeManager* getInstance();
	ShapeManager(ShapeManager& other) = delete;
	void operator= (const ShapeManager &) = delete;
	void addPolygon(Polygon * polygon);
	void addThreeDimensionalFigure(ThreeDimensionalFigure * threeDimensionalFigure);
	void renderAll();
	void selectPolygon(Point point);
	void processTranslation(float dx, float dy);
	void processScaling(float sx, float sy);
	void processRotation(float angle);
	void setDimension(DIMENSION dimension);
};
