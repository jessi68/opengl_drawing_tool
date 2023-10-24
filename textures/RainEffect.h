#ifndef RAIN_EFFECT_H
#define RAIN_EFFECT_H
#include "Cube.h"
#include "Shader.h"
#include <vector>

class RainEffect : public Shape
{
private:
	Shader* shader;
	int raindropNumber;
	float halfOfRainDropSize;
	float previousTime;
	float velocity;
	float interval;
	vector<Cube*> rainDrops;
public:
	RainEffect(int rainDropNumber = 4);
	void setShader(Shader* shader);
	~RainEffect();
	virtual void render();
};

#endif
