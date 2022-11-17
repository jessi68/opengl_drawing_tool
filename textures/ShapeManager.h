
#include <vector>
#include "Triangle.h"
#include "Dimension.h"
#include "ThreeDimensionalFigure.h"
#include "Camera.h"
#include "RainEffect.h"

using namespace std;

class ShapeManager
{
private:
	static ShapeManager* drawingManager;
	TYPE dimension = THREE;
	ShapeManager();
	vector<Polygon*> polygons;
	vector<ThreeDimensionalFigure*> threeDimensionFigures;
	vector<Polygon*> countourPolygons;
	RainEffect* rainEffect;
	// 객체 두번 생성하는 거 막으려고 포인터로 함
	Shader* basic2DShader;
	Shader* basic3DShader;
	int polygonNumber;
	int threeDimensionalFigureNumber;
	int selectedPolygonIndex;
	int selectedThreeDimensionalFigureIndex;
	// camera
	Camera * camera;
	glm::mat4 projection;
	static void Destroy();
	bool isValidIndex3d(int index);
public:
	/**
	* Singletons should not be cloneable.
	* =delete: prohibiting copying
	*/
	static ShapeManager* getInstance();
	ShapeManager(ShapeManager& other) = delete;
	void operator= (const ShapeManager &) = delete;
	void addEffect(RainEffect* rainEffect);
	void addPolygon(Polygon * polygon);
	void addThreeDimensionalFigure(ThreeDimensionalFigure * threeDimensionalFigure);
	void renderAll();
	void selectPolygon(Point point);
	void selectThreeDimensionalFigure(int index);
	void processTranslation(float dx, float dy, float dz);
	void processScaling(float sx, float sy);
	void processRotation(float angle);
	void setDimension(TYPE dimension);
	void changeToTranslationModeIn3d();
	void changeToScaleModeIn3d();
	void processScalingIn3d(GLfloat color[3], int index, float offset, float depthOffset);
	void rotateIn3D(glm::mat4 rogridMatrix);
	void moveCamera(float xoffset, float yoffset);
	void processKeyBoard(CameraMovement direction, float deltaTime);
};
