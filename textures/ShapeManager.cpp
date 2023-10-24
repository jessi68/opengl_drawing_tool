#include "ShapeManager.h"
#include "PolygonAlgorithm.h"
#include "ScreenProperty.h"

void ShapeManager::initialize() {
    this->basic2DShader = new Shader("2d_shape.vert", "2d_shape.frag");
    this->basic3DShader = new Shader("3d_shape.vert", "3d_shape.frag");

    this->camera = new Camera(glm::vec3(-0.3f, 0.2f, 1.0f));
    this->projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    this->polygonNumber = 0;
    this->selectedThreeDimensionalFigureIndex = -1;
    this->selectedPolygonIndex = -1;
    this->threeDimensionalFigureNumber = 0;
}

ShapeManager::ShapeManager()
{
    initialize();
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

void ShapeManager::addEffect(RainEffect* rainEffect)
{
    this->rainEffect = rainEffect;
}

// const 객체를 함수 파라미터로 받아오면 멤버함수 불러오는거 자체가 불가능
void ShapeManager::addPolygon(Polygon * polygon)
{
    this->rainEffect = NULL;
    polygons.push_back(polygon);
    this->polygonNumber += 1;
}

void ShapeManager::addThreeDimensionalFigure(ThreeDimensionalFigure* threeDimensionalFigure)
{
    this->rainEffect = NULL;
    threeDimensionFigures.push_back(threeDimensionalFigure);
    this->threeDimensionalFigureNumber += 1;

}

void ShapeManager::renderAll()
{  
    // 나중에 시간될 때 리팩토링 ㄱ ㄱ
   
    if (this->dimension == TWO) {
        glEnable(GL_DEPTH_TEST);
        this->basic2DShader->use();

        for (int i = 0; i < this->polygonNumber; i++) {

            polygons[i]->setShaderValue(this->basic2DShader);
            polygons[i]->render();

            if (this->selectedPolygonIndex == i) {
                // 소수를 정확하게 표현할 수 없는 것 때문에 scaling 하고 원래대로 복원하는 건 어려움. 

                // 시간될 때 아래 코드 리팩토링하기 matrix scali
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
  
        this->basic3DShader->use();
        this->basic3DShader->setMat4("projection", projection);
        this->basic3DShader->setMat4("view", camera->GetViewMatrix());
        this->basic3DShader->setFloat("znear", 0.1);
        this->basic3DShader->setFloat("zfar", 100);

        glClearStencil(0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
            cout << "Error";
        glEnable(GL_STENCIL_TEST);
        glDepthFunc(GL_LESS);
        glDepthRange(0.1, 100);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        if (this->rainEffect != NULL) {
            this->rainEffect->setShader(this->basic3DShader);
            this->rainEffect->render();
        }
        else {

            for (int i = 0; i < this->threeDimensionalFigureNumber; i++) {
                glStencilFunc(GL_ALWAYS, i + 1, 1);

                threeDimensionFigures[i]->setShaderValue(this->basic3DShader);
                threeDimensionFigures[i]->render();

                if (this->selectedThreeDimensionalFigureIndex == i) {
                    threeDimensionFigures[i]->setShaderValue(this->basic3DShader);
                    this->basic3DShader->setVec3("color", 0.0, 0.0, 0.0);
                    threeDimensionFigures[i]->renderCoordinate(basic3DShader);
                }
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
    if (isValidIndex3d(index)) {
        this->selectedThreeDimensionalFigureIndex = index;
    }
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

void ShapeManager::changeDimension(TYPE dimension)
{
    this->initialize();
    this->dimension = dimension;
}

void ShapeManager::changeToTranslationModeIn3d() {
    if (selectedThreeDimensionalFigureIndex != -1) {
        this->threeDimensionFigures[selectedThreeDimensionalFigureIndex]->changeToTransfomationMode();
    }
}

void ShapeManager::changeToScaleModeIn3d() {
    if (selectedThreeDimensionalFigureIndex != -1) {
        this->threeDimensionFigures[selectedThreeDimensionalFigureIndex]->changeToScaleMode();
    }
}

bool ShapeManager::isValidIndex3d(int index) {
    return index >= 0 && index < this->threeDimensionalFigureNumber;
}

void ShapeManager::processScalingIn3d(GLfloat color[3], int index, float offset, float depthOffset) {
    int coordinateIndex;
    if (index == selectedThreeDimensionalFigureIndex) {
        coordinateIndex = this->threeDimensionFigures[selectedThreeDimensionalFigureIndex]->isScalingPossible(color);
       
        if (coordinateIndex != -1) {
            if (coordinateIndex == 2) {
                cout << " z z" << endl;
                offset = depthOffset;
         
            }
            cout <<  "offset" << offset << endl;
            this->threeDimensionFigures[selectedThreeDimensionalFigureIndex]->scale(offset, coordinateIndex);
        }
    }
}

void ShapeManager::rotateIn3D(glm::mat4 rogridMatrix)
{
    if (this->selectedThreeDimensionalFigureIndex != -1) {
        this->threeDimensionFigures[this->selectedThreeDimensionalFigureIndex]->transformation(rogridMatrix);
    }
}

void ShapeManager::moveCamera(float xoffset, float yoffset) {
    camera->ProcessMouseMovement(xoffset, yoffset);
}

void ShapeManager::processKeyBoard(CameraMovement direction, float deltaTime) {
    camera->ProcessKeyboard(direction, deltaTime);
}
ShapeManager* ShapeManager::drawingManager = nullptr;