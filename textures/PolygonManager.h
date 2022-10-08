#include <vector>
#include "Triangle.h"
#include "Shader.h"

using namespace std;

// sigleton
class PolygonManager
{
private:
	static PolygonManager* drawingManager;
	PolygonManager();
	vector<Polygon*> polygonsToRender;
	vector<Polygon*> countourPolygons;
	// 객체 두번 생성하는 거 막으려고 포인터로 함
	Shader* basicShader;
	int polygonNumber;
	int selectedPolygonIndex;
	static void Destroy();
public:
	/**
	* Singletons should not be cloneable.
	* =delete: prohibiting copying
	*/
	static PolygonManager* getInstance();
	PolygonManager(PolygonManager& other) = delete;
	void operator= (const PolygonManager &) = delete;
	void addPolygon(Polygon* polygon);
	void renderAll();
	void selectPolygon(Point point);
	void processTranslation(float dx, float dy);
	void processScaling(float sx, float sy);
	void processRotation(float angle);
};
