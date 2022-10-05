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
	// ��ü �ι� �����ϴ� �� �������� �����ͷ� ��
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
	void addPolygon(Polygon* shape);
	void renderAll();
	void selectPolygon(Point point);
	void processKeyboard(float dx, float dy);
};
