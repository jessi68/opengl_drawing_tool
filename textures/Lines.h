#include "Shape.h"

//rectangle �� �׸���
class Lines : public Shape
{
public:
	Lines();
	Lines(float* vertices, vector<unsigned int> vertexAttributeNumbers, unsigned int eachAttributeNumber, unsigned int totalVerticeNumber);
	void copyFrom(const Lines& src);
	Lines(const Lines& src);
	Lines& operator=(const Lines& lines);
	void render() override;
};

