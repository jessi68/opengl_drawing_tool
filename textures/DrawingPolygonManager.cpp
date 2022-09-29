#include "DrawingPolygonManager.h"

DrawingPolygonManager::DrawingPolygonManager()
{
    this->basicShader = new Shader("2d_shape.vert", "2d_shape.frag");
}



DrawingPolygonManager* DrawingPolygonManager::getInstance() {
    if (DrawingPolygonManager::drawingManager == nullptr) {
        DrawingPolygonManager::drawingManager = new DrawingPolygonManager();
        atexit(Destroy);
    }
    return DrawingPolygonManager::drawingManager;
}

void DrawingPolygonManager::Destroy() {
    vector<Shape*> polygonsToRender = DrawingPolygonManager::drawingManager->polygonsToRender;
    for (auto polygons : polygonsToRender) {
        delete polygons;
    }
    delete DrawingPolygonManager::drawingManager->basicShader;
    delete DrawingPolygonManager::drawingManager;
}

void DrawingPolygonManager::addPolygon(Shape * shape)
{
    polygonsToRender.push_back(shape);
}

void DrawingPolygonManager::renderAll()
{  
    int size = polygonsToRender.size();
    for (int i = 0; i < size; i++) {
        polygonsToRender[i]->render();
    }
}

void DrawingPolygonManager::activateBasicShader() {
    basicShader->setVec3("color", 0.0f, 0.0f, 1.0f);
    basicShader->use();
}

DrawingPolygonManager* DrawingPolygonManager::drawingManager = nullptr;