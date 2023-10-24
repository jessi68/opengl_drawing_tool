#include "RainEffect.h"

RainEffect::RainEffect(int raindropNumber)
{
	this->raindropNumber = raindropNumber;
    this->previousTime = static_cast<float>(glfwGetTime());
    this->shader = NULL;
    this->velocity = -0.1;
    this->halfOfRainDropSize =  0.05;
    this->interval = this->halfOfRainDropSize * 2 + 0.05;
   

    float dx = -0.47;
    float oddY = 0.46;
    float evenY = 0.43;
    float dy;

    cout << raindropNumber << " rrrdddd" << endl;
	for (int i = 0; i < raindropNumber; i++) {
        float* vertices = new float[24] {
            -halfOfRainDropSize, halfOfRainDropSize, -halfOfRainDropSize,  //Point A 0
            -halfOfRainDropSize, halfOfRainDropSize, halfOfRainDropSize,//Point B 1
            halfOfRainDropSize, halfOfRainDropSize, -halfOfRainDropSize,//Point C 2
            halfOfRainDropSize, halfOfRainDropSize, halfOfRainDropSize, //Point D 3
            -halfOfRainDropSize, -halfOfRainDropSize, -halfOfRainDropSize, //Point E 4
            -halfOfRainDropSize, -halfOfRainDropSize, halfOfRainDropSize,//Point F 5
            halfOfRainDropSize, -halfOfRainDropSize, -halfOfRainDropSize,//Point G 6
            halfOfRainDropSize, -halfOfRainDropSize, halfOfRainDropSize//Point H 7
        };

		(this->rainDrops).push_back(new Cube(vertices));
        
        if (i % 2 == 1) {
            dy = evenY;
        }
        else {
            dy = oddY;
        }

        this->rainDrops[i]->translation(dx, dy, 0);
        dx += interval;
	}
}

void RainEffect::setShader(Shader* shader)
{
    this->shader = shader;
}

RainEffect::~RainEffect()
{
    for (int i = 0; i < this->raindropNumber; i++) {
        delete this->rainDrops[i];
    }
}

void RainEffect::render()
{
    float currentTime = static_cast<float>(glfwGetTime());
    float deltaTime = currentTime - this->previousTime;
    glm::mat4 matrix;
	for (int i = 0; i < this->raindropNumber; i++) {
        this->rainDrops[i]->translation(0, deltaTime * velocity,0);
        matrix = this->rainDrops[i]->getMatrix();
        cout << matrix[3][1] << " yyyy" << endl;
        if (abs(matrix[3][1] - -0.14) < 0.01) {
            this->rainDrops[i]->setPosition(-0.47 + this->interval * i, 0.46, 0);
        }
        this->rainDrops[i]->setShaderValue(this->shader);
        this->rainDrops[i]->render();
        
	}
    this->previousTime = currentTime;
}
