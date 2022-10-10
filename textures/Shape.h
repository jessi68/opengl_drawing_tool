#include <glm/glm.hpp>
#include  <vector>

using namespace std;

// ���� �� �ִٸ� �߻�Ŭ������ ����� �ʹ�. 
class Shape
{
protected:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int eachAttributeNumber;
	unsigned int totalVerticeNumber;
	unsigned int totalCoordinateNumber;
	unsigned int totalIndiceNumber;
	float* verticeAttributes;
	vector<unsigned int> vertexAttributeNumbers;
	unsigned int* indices;
	glm::vec3 color;
	glm::mat4 matrix;
	void initiliazeVertexBufferDatas();
public:
	Shape();
	Shape(float* vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber, unsigned int totalVerticeNumber);
	~Shape();
	void copyFrom(const Shape& src);
	Shape(const Shape& src);
	Shape& operator=(const Shape& shape);
	void render();
};

