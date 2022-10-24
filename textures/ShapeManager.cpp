#include "ShapeManager.h"
#include "PolygonAlgorithm.h"
#include "ScreenProperty.h"

ShapeManager::ShapeManager()
{
    this->basic2DShader = new Shader("2d_shape.vert", "2d_shape.frag");
    this->basic3DShader = new Shader("3d_shape.vert", "3d_shape.frag");
    this->camera = new Camera(glm::vec3(-0.3f, 0.2f, 1.0f));
    this->projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    this->polygonNumber = 0;
    this->selectedThreeDimensionalFigureIndex = -1;
    this->selectedPolygonIndex = -1;
    this->threeDimensionalFigureNumber = 0;
}

ShapeManager* ShapeManager::getInstance() {
    if (ShapeManager::drawingManager == nullptr) {
        ShapeManager::drawingManager = new ShapeManager();
    }
    return ShapeManager::drawingManager;
}

void ShapeManager::Destroy() {
   
    /*for (auto polygons : polygonsToRender) {
        delete polygons;
    }*/
  
    delete ShapeManager::drawingManager->camera;
    delete ShapeManager::drawingManager->basic2DShader;
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
        glEnable(GL_DEPTH_TEST);
        this->basic2DShader->use();

        for (int i = 0; i < this->polygonNumber; i++) {

            polygons[i]->setShaderValue(this->basic2DShader);
            polygons[i]->render();

            if (this->selectedPolygonIndex == i) {
                // �Ҽ��� ��Ȯ�ϰ� ǥ���� �� ���� �� ������ scaling �ϰ� ������� �����ϴ� �� �����. 

                // �ð��� �� �Ʒ� �ڵ� �����丵�ϱ� matrix scali
                glm::mat4 changedMatrix = polygons[i]->getMatrix();
                glm::mat4 scaleMatrix = glm::mat4(1.0f);
                scaleMatrix[0][0] = 1.1f;
                scaleMatrix[1][1] = 1.1f;
                changedMatrix = changedMatrix * scaleMatrix;

                glm::mat4 transMatrix = glm::mat4(1.0f);
                transMatrix[3][0] = -0.0;
                transMatrix[3][1] = -0.01;

                changedMatrix = transMatrix * changedMatrix;
                basic2DShader->setMat4("transformation", changedMatrix);
                basic2DShader->setVec3("color", 1.0, 1.0, 0.0);
                polygons[i]->render();
            }
        }
    }
    else {
        glDisable(GL_DEPTH_TEST);

        this->basic3DShader->use();
        this->basic3DShader->setMat4("projection", projection);
        this->basic3DShader->setMat4("view", camera->GetViewMatrix());

        glClearStencil(0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glEnable(GL_STENCIL_TEST);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        for (int i = 0; i < this->threeDimensionalFigureNumber; i++) {
            glStencilFunc(GL_ALWAYS, i + 1, -1);

            if (this->selectedThreeDimensionalFigureIndex == i) {
                glm::mat4 changedMatrix = threeDimensionFigures[i]->getMatrix();
                glm::mat4 scaleMatrix = glm::mat4(1.0f);
                scaleMatrix[0][0] = 1.1f;
                scaleMatrix[1][1] = 1.1f;
                scaleMatrix[2][2] = 1.1f;
                changedMatrix = changedMatrix * scaleMatrix;

                glm::mat4 transMatrix = glm::mat4(1.0f);
                transMatrix[3][0] = -0.0;
                transMatrix[3][1] = -0.01;

                changedMatrix = transMatrix * changedMatrix;
                basic3DShader->setMat4("transformation", changedMatrix);
                basic3DShader->setVec3("color", 1.0, 1.0, 0.0);
                threeDimensionFigures[i]->render();
            }
           
            threeDimensionFigures[i]->setShaderValue(this->basic3DShader);
            threeDimensionFigures[i]->render();

            if (this->selectedThreeDimensionalFigureIndex == i) {
                threeDimensionFigures[i]->setShaderValue(this->basic3DShader);
                this->basic3DShader->setVec3("color", 0.0, 0.0, 1.0);
                threeDimensionFigures[i]->renderCoordinate();
            }
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

void ShapeManager::selectThreeDimensionalFigure(int index)
{
    this->selectedThreeDimensionalFigureIndex = index;
}

void ShapeManager::processTranslation(float dx, float dy, float dz)
{
    if (this->dimension == TWO) {
        if (this->selectedPolygonIndex != -1) {
            polygons[this->selectedPolygonIndex]->translation(dx, dy);
        }
    }
    else {
        if (this->selectedThreeDimensionalFigureIndex != -1) {
            threeDimensionFigures[this->selectedThreeDimensionalFigureIndex]->translation(dx, dy, dz);
        }
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

void ShapeManager::processMouseMovement(float xoffset, float yoffset)
{
    this->camera->ProcessMouseMovement(xoffset, yoffset);
}

ShapeManager* ShapeManager::drawingManager = nullptr;