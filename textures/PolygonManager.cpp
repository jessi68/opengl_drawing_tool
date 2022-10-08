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

void PolygonManager::addPolygon(Polygon * polygon)
{
    polygonsToRender.push_back(polygon);

    this->polygonNumber += 1;
}

void PolygonManager::renderAll()
{  
    glEnable(GL_DEPTH_TEST);
    this->basicShader->use();
    for (int i = 0; i < this->polygonNumber; i++) {
       
        polygonsToRender[i]->setShaderValue(this->basicShader);
        polygonsToRender[i]->render();

        if (this->selectedPolygonIndex == i) {
            // 소수를 정확하게 표현할 수 없는 것 때문에 scaling 하고 원래대로 복원하는 건 어려움. 
    
            glm::mat4 changedMatrix = polygonsToRender[i]->getMatrix();
            glm::mat4 scaleMatrix = glm::mat4(1.0f);
            scaleMatrix[0][0] = 1.1f;
            scaleMatrix[1][1] = 1.1f;
            changedMatrix = changedMatrix * scaleMatrix;

            glm::mat4 transMatrix = glm::mat4(1.0f);
            transMatrix[3][0] = -0.0;
            transMatrix[3][1] = -0.01;

            changedMatrix = transMatrix * changedMatrix;
            basicShader->setMat4("transformation", changedMatrix);
            basicShader->setVec3("color", 1.0, 1.0, 0.0);
            polygonsToRender[i]->render();
      
           
        }       
    }
}

void PolygonManager::selectPolygon(Point point)
{
    for (int i = 0; i < this->polygonNumber; i++) {
        cout << "selecting" << endl;
        if (this->polygonsToRender[i]->isIncludePoint(point)) {
            this->selectedPolygonIndex = i;
            break;
        }
    }
    
}

void PolygonManager::processTranslation(float dx, float dy)
{
    if (this->selectedPolygonIndex != -1) {
          polygonsToRender[this->selectedPolygonIndex]->translation(dx, dy);
    }
}

void PolygonManager::processScaling(float sx, float sy)
{
    if (this->selectedPolygonIndex != -1) {
        polygonsToRender[this->selectedPolygonIndex]->scale(sx, sy);
    }
}

void PolygonManager::processRotation(float angle)
{
    if (this->selectedPolygonIndex != -1) {
        polygonsToRender[this->selectedPolygonIndex]->rotate(angle);
    }
}

PolygonManager* PolygonManager::drawingManager = nullptr;