#include <vector>
#include "Triangle.h"
#include "Shader.h"

using namespace std;

// sigleton
class DrawingPolygonManager
{
private:
	static DrawingPolygonManager* drawingManager;
	DrawingPolygonManager();
	vector<Shape*> polygonsToRender;
	// 객체 두번 생성하는 거 막으려고 포인터로 함
	Shader * basicShader;

	static void Destroy();
public:
	/**
	* Singletons should not be cloneable.
	* =delete: prohibiting copying
	*/
	static DrawingPolygonManager* getInstance();
	DrawingPolygonManager(DrawingPolygonManager& other) = delete;
	void operator= (const DrawingPolygonManager &) = delete;
	void addPolygon(Shape* shape);
	void renderAll();
	void activateBasicShader();
};
