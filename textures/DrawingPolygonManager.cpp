#include "DrawingPolygonManager.h"

DrawingPolygonManager::DrawingPolygonManager()
{
}

DrawingPolygonManager* DrawingPolygonManager::getInstance() {
    if (DrawingPolygonManager::drawingManager == nullptr) {
        DrawingPolygonManager::drawingManager = new DrawingPolygonManager();
        atexit(Destroy);
    }
    return DrawingPolygonManager::drawingManager;
}

void DrawingPolygonManager::Destroy() {
    
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

DrawingPolygonManager* DrawingPolygonManager::drawingManager = nullptr;