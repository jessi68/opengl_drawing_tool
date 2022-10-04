#include "PolygonManager.h"
#include "PolygonAlgorithm.h"

PolygonManager::PolygonManager()
{
    this->basicShader = new Shader("2d_shape.vert", "2d_shape.frag");
    this->polygonNumber = 0;
    this->selectedPolygonIndex = -1;
    
}

PolygonManager* PolygonManager::getInstance() {
    if (PolygonManager::drawingManager == nullptr) {
        PolygonManager::drawingManager = new PolygonManager();
        // 소멸자 바꾸기
        atexit(Destroy);
    }
    return PolygonManager::drawingManager;
}

void PolygonManager::Destroy() {
    vector<Polygon*> polygonsToRender = PolygonManager::drawingManager->polygonsToRender;
    for (auto polygons : polygonsToRender) {
        delete polygons;
    }
    delete PolygonManager::drawingManager->basicShader;
    delete PolygonManager::drawingManager;
}

void PolygonManager::addPolygon(Polygon * shape)
{
    polygonsToRender.push_back(shape);
    this->polygonNumber += 1;
}

void PolygonManager::renderAll()
{  
    for (int i = 0; i < this->polygonNumber; i++) {
        if (this->selectedPolygonIndex == i) {
            basicShader->setVec3("color", 1.0, 1.0, 0.0);
            polygonsToRender[i]->render();
        }
        polygonsToRender[i]->setShaderValue(this->basicShader);
        this->basicShader->use();
        polygonsToRender[i]->render();
    }
}

void PolygonManager::activateBasicShader() {
    basicShader->setVec3("color", 0.0f, 0.0f, 1.0f);
    basicShader->use();
}

void PolygonManager::selectPolygon(Point point)
{
    for (int i = 0; i < this->polygonNumber; i++) {

        if (this->polygonsToRender[i]->isIncludePoint(point)) {
            this->selectedPolygonIndex = i;
            cout << "selected" << endl;
            break;
        }
    }
    
}

void PolygonManager::processKeyboard(float dx, float dy)
{
    if (this->selectedPolygonIndex != -1) {
          polygonsToRender[this->selectedPolygonIndex]->translation(dx, dy);
    }
}

PolygonManager* PolygonManager::drawingManager = nullptr;