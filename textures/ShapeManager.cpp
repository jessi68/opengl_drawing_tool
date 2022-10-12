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

// const ��ü�� �Լ� �Ķ���ͷ� �޾ƿ��� ����Լ� �ҷ����°� ��ü�� �Ұ���
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
    // ���߿� �ð��� �� �����丵 �� ��
    if (this->dimension == TWO) {
        this->basicShader->use();

        for (int i = 0; i < this->polygonNumber; i++) {

            polygons[i]->setShaderValue(this->basicShader);
            polygons[i]->render();

            if (this->selectedPolygonIndex == i) {
                // �Ҽ��� ��Ȯ�ϰ� ǥ���� �� ���� �� ������ scaling �ϰ� ������� �����ϴ� �� �����. 

                // �ð��� �� �Ʒ� �ڵ� �����丵�ϱ� matrix scali
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