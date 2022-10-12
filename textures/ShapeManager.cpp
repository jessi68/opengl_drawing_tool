#include "ShapeManager.h"
#include "PolygonAlgorithm.h"

ShapeManager::ShapeManager()
{
    this->basicShader = new Shader("2d_shape.vert", "2d_shape.frag");
    this->polygonNumber = 0;
    this->selectedPolygonIndex = -1;
}

ShapeManager* ShapeManager::getInstance() {
    if (ShapeManager::drawingManager == nullptr) {
        ShapeManager::drawingManager = new ShapeManager();
        //atexit(Destroy);
    }
    return ShapeManager::drawingManager;
}

void ShapeManager::Destroy() {
   
    /*for (auto polygons : polygonsToRender) {
        delete polygons;
    }*/
  
    delete ShapeManager::drawingManager->basicShader;
    delete ShapeManager::drawingManager;
}

// const 객체를 함수 파라미터로 받아오면 멤버함수 불러오는거 자체가 불가능
void ShapeManager::addPolygon(Polygon * polygon)
{
    polygons.push_back(polygon);
    this->polygonNumber += 1;
}

void ShapeManager::addThreeDimensionalFigure(ThreeDimensionalFigure* threeDimensionalFigure)
{
    threeDimensionFigures.push_back(threeDimensionalFigure);
    this->threeDimensionalFigureNumber += 1;

}

void ShapeManager::renderAll()
{  
    // 나중에 시간될 때 리팩토링 ㄱ ㄱ
    if (this->dimension == TWO) {
        this->basicShader->use();

        for (int i = 0; i < this->polygonNumber; i++) {

            polygons[i]->setShaderValue(this->basicShader);
            polygons[i]->render();

            if (this->selectedPolygonIndex == i) {
                // 소수를 정확하게 표현할 수 없는 것 때문에 scaling 하고 원래대로 복원하는 건 어려움. 

                // 시간될 때 아래 코드 리팩토링하기 matrix scali
                glm::mat4 changedMatrix = polygons[i]->getMatrix();
                glm::mat4 scaleMatrix = glm::mat4(1.0f);
                scaleMatrix[0][0] = 1.1f;
                scaleMatrix[1][1] = 1.1f;
                changedMatrix = changedMatrix * scaleMatrix;

                cout << " is iit work " << endl;

                glm::mat4 transMatrix = glm::mat4(1.0f);
                transMatrix[3][0] = -0.0;
                transMatrix[3][1] = -0.01;

                changedMatrix = transMatrix * changedMatrix;
                basicShader->setMat4("transformation", changedMatrix);
                basicShader->setVec3("color", 1.0, 1.0, 0.0);
                polygons[i]->render();
            }
        }
    }
    else {
        this->basicShader->use();
        cout << "three dimensional" << endl;

        for (int i = 0; i < this->threeDimensionalFigureNumber; i++) {
            threeDimensionFigures[i]->setShaderValue(this->basicShader);
            threeDimensionFigures[i]->render();
        }
    }
}

void ShapeManager::selectPolygon(Point point)
{
    for (int i = 0; i < this->polygonNumber; i++) {
        if (this->polygons[i]->isIncludePoint(point)) {
            this->selectedPolygonIndex = i;
            break;
        }
    }
    
}

void ShapeManager::processTranslation(float dx, float dy)
{
    if (this->selectedPolygonIndex != -1) {
          polygons[this->selectedPolygonIndex]->translation(dx, dy);
    }
}

void ShapeManager::processScaling(float sx, float sy)
{
    if (this->selectedPolygonIndex != -1) {
        polygons[this->selectedPolygonIndex]->scale(sx, sy);
    }
}

void ShapeManager::processRotation(float angle)
{
    if (this->selectedPolygonIndex != -1) {
        polygons[this->selectedPolygonIndex]->rotate(angle);
    }
}

void ShapeManager::setDimension(DIMENSION dimension)
{
    this->dimension = dimension;
}

ShapeManager* ShapeManager::drawingManager = nullptr;