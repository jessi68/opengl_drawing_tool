#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Dimension.h"
#include "Shader.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "Cube.h"
#include "RainEffect.h"
#include "ShapeManager.h"
#include "ScreenProperty.h"

#include <iostream>
#include <stdio.h>

using namespace std;

enum TRANSFORMATION_MODE
{
    ROTATION,
    SCALE
};

void makePolygonUI(ShapeManager* shapeManager);
void makeTransformationUI();
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow* window);
float distance(float x, float y, float destX, float destY);

unsigned int loadTexture(const char* path);

// settings
TRANSFORMATION_MODE transformationMode = SCALE;
DIMENSION dimension = THREE;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
float lastDepth;
bool firstMouse = true;
bool isUIClicked = false;
bool isMouseClicked = false;
bool isRotation = false;

// timing
float speed = 0.3f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

ShapeManager* shapeManager;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_callback);


    // tell GLFW to capture our mouse
   

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

   
    // make Drawing manager singleton
    shapeManager = ShapeManager::getInstance();
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
  
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glsl_version = "#version 330";
    ImGui_ImplOpenGL3_Init(glsl_version);

   
    // build and compile our shader zprogram
    // ------------------------------------
  
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------


    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
       // -----
        processInput(window);

        // render
        // ------
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::SetNextWindowSize(ImVec2(100, 180));
        ImGui::Begin("polygon");
        // pass singleton as parameter 
        makePolygonUI(shapeManager);
        makeTransformationUI();
        ImGui::End();


        shapeManager->renderAll();
      
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void makePolygonUI(ShapeManager * drawingPolygonManager) {
   
    if (ImGui::Button("change coordinate")) {
        if (dimension == TWO) {
            dimension = THREE;
        }
        else {
            dimension = TWO;
        }
        shapeManager->setDimension(dimension);
    }
    if (dimension == TWO) {
        if (ImGui::Button("triangle")) {
            float* vertices = new float[9] {
                // vertex  
                -0.2, 0.0, 0,
                 0, 0.4, 0,
                 0.2, 0.0, 0
            };

            drawingPolygonManager->addPolygon(new Triangle(vertices));
        }
        if (ImGui::Button("rectangle")) {
            float* vertices = new float[12] {
                // vertex  
                -0.2, 0.0, 0,
                -0.2, 0.4, 0,
                0.2, 0.0, 0,
                0.2, 0.4, 0,
            };
            drawingPolygonManager->addPolygon(new Rectangle(vertices));
        }
    }
    else {
        if (ImGui::Button("cube")) {
            float* vertices = new float[24] {
                -0.1f, 0.1f, -0.1f,  //Point A 0
                -0.1f, 0.1f, 0.1f,//Point B 1
                0.1f, 0.1f, -0.1f,//Point C 2
                0.1f, 0.1f, 0.1f, //Point D 3
                -0.1f, -0.1f, -0.1f, //Point E 4
                -0.1f, -0.1f, 0.1f,//Point F 5
                0.1f, -0.1f, -0.1f,//Point G 6
                0.1f, -0.1f, 0.1f//Point H 7
            };
            drawingPolygonManager->addThreeDimensionalFigure(new Cube(vertices));
        }
        if (ImGui::Button("RainEffect")) {
            drawingPolygonManager->addEffect(new RainEffect());
        }
    }
   
}

void makeTransformationUI() 
{
    ImGui::Text("transformation");
    if (dimension == TWO) {
        if (ImGui::Button("rotation")) {
            transformationMode = ROTATION;
        }
        if (ImGui::Button("scale")) {
            transformationMode = SCALE;
        }
    }
    else {
        if (ImGui::Button("trnaformation")) {
            shapeManager->changeToTranslationModeIn3d();
        } 
        if (ImGui::Button("scale")) {
            shapeManager->changeToScaleModeIn3d();
        }
        if (ImGui::Button("rotation")) {
            cout << "rrrr" << endl;
            isRotation = true;
        }
    }
  
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    float dx = 0, dy = 0;
    float dz = 0;
    float distance = deltaTime * speed;

    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        shapeManager->processScaling(0.8, 0.8);
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        dy = distance;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        dy = -1 * distance;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        dx = -1 * distance;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        dx = distance;

    if (glfwGetKey(window, GLFW_KEY_UP)) {
        dz = distance;
    } if (glfwGetKey(window, GLFW_KEY_DOWN)) {
        dz = -1 * distance;
    }

     shapeManager->processTranslation(dx, dy, dz);
        
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

Point changeFromWindowToWorld(double x, double y) {
    return Point(x * 2 / SCR_WIDTH - 1, (SCR_HEIGHT - y) * 2 / SCR_HEIGHT - 1);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        isMouseClicked = true;
        firstMouse = true;
        double x, y;
        //getting cursor position
        glfwGetCursorPos(window, &x, &y);

        if (dimension == TWO) {
            Point currentPoint = changeFromWindowToWorld(x, y);
          
            shapeManager->selectPolygon(currentPoint);
        }
        else {
            GLuint index;
            GLfloat depth;
           
            glReadPixels(x, SCR_HEIGHT - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
            glReadPixels(x, SCR_HEIGHT - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
            cout << "depth " << depth << endl;

            // 배경, ui 등을 클릭했을 때
            if (index == 0) {
                return;
            }

            //cout << index << "click " << index << endl;
            shapeManager->selectThreeDimensionalFigure(index - 1);

        }
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT and action == GLFW_RELEASE) {
        isMouseClicked = false;
    }
}

float distance(float x, float y, float destX, float destY) {
    return pow((x - destX) * (x - destX) + (y - destY) * (y - destY), 0.5);
}

double norm(double * point, int size) {
    double value = 0;

    for (int i = 0; i < size; i++) {
        value += point[i] * point[i];
    }

    return (double) pow(value, 0.5);
}

double cross(double start[2], double dest[2]) {
    return start[0] * dest[1] - start[1] * dest[0];
}

double* crossIn3d(double start[3], double dest[3]) {
    double * result = new double[3] {
        start[1] * dest[2] - start[2] * dest[1], 
        start[2] * dest[0] - start[0] * dest[2],
        start[0] * dest[1] - start[1] * dest[0]
    };
    return result;
}

double* scaleDownToSphere(double* point, double squaredRadius) {
    if (point[0] < 0.0001 && point[0] > -0.0001) {
        point[1] = squaredRadius * 0.95;
        return point;
    }
    else {
        float previousX = point[0];
        if (point[0] < 0) {
            point[0] = -1 * pow((squaredRadius * 0.95) / (1 + ((point[1] * point[1]) / (point[0] * point[0]))), 0.5);
        }
        else {
            point[0] = pow((squaredRadius * 0.95) / (1 + ((point[1] * point[1]) / (point[0] * point[0]))), 0.5);
        }
        point[1] = (point[1] / previousX) * point[0];
        return point;
    }
}

glm::mat3 virtualTrackball(double startX, double startY, double destX,  double destY) {

    double radius = min(SCR_WIDTH, SCR_HEIGHT) / (double)2;

    float squaredRadius = radius * radius;

    float half_width = SCR_WIDTH / (double) 2;
    float half_height = SCR_HEIGHT / (double) 2;

    double* start = new double[2] {startX - half_width, startY - half_height};
    double* dest = new double[2] { destX - half_width, destY - half_height };


    double startNorm = norm(start, 2);
    double destNorm = norm(dest, 2);

    if (startNorm * startNorm > squaredRadius) {
        start = scaleDownToSphere(start, squaredRadius);
        cout << "is scale down src" << endl;
    }

    if (destNorm * destNorm > squaredRadius) {
        dest = scaleDownToSphere(dest, squaredRadius);
        cout << "is scale down dest" << endl;
    }

    double theta = cross(start, dest) / (startNorm * destNorm);
    double start3D[3] = { start[0], start[1], pow(squaredRadius - (start[0] * start[0] + start[1] * start[1]), 0.5) };
    double dest3D[3] = { dest[0], dest[1], pow(squaredRadius - (dest[0] * dest[0] + dest[1] * dest[1]), 0.5) };

    double* normalVector = crossIn3d(start3D, dest3D);
    double normOfVector = norm(normalVector, 3);

    cout << normOfVector << " norm" << endl;
    cout << "normal vector" << endl;
    for (int i = 0; i < 3; i++) {
        cout << normalVector[i] << endl;
        normalVector[i] = normalVector[i] / normOfVector;
        cout << normalVector[i] << endl;
    }

    cout << endl;

    glm::mat3 crossProductK(0);
    crossProductK[1][0] = -1 * normalVector[2];
    crossProductK[2][0] = normalVector[1];
    crossProductK[0][1] = normalVector[2];
    crossProductK[2][1] = -normalVector[0];
    crossProductK[0][2] = -normalVector[1];
    crossProductK[1][2] = normalVector[0];

    //{ {0, -1 * normalVector[2], normalVector[1]}, { normalVector[2], 0, -normalVector[0] }, { -normalVector[1], normalVector[0], 0 }};

    delete[] normalVector;
    delete[] start;
    delete[] dest;

    cout << theta << " theta" << endl;
    return glm::mat3(1.0f) + (float) theta * crossProductK + (crossProductK * crossProductK) * (float) (1 - cos(theta));
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    GLbyte color[3];
    GLfloat colorf[3];
    GLuint index;
    GLfloat depth;
    float dist;

    if (isMouseClicked) {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (firstMouse)
        {
            glReadPixels(xpos, SCR_HEIGHT - ypos - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
            lastX = xpos;
            lastY = ypos;
            lastDepth = depth;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
        
        float normalizedX = xoffset * 2 / SCR_WIDTH;
        float normalizedY = yoffset * 2 / SCR_HEIGHT;

        if (dimension == TWO) {
            if (transformationMode == SCALE) {
                shapeManager->processScaling(normalizedX, normalizedY);
            }
            else {
                shapeManager->processRotation(normalizedX + normalizedY);
            }
        }
        else {
            if (!isRotation) {
                glReadPixels(xpos, SCR_HEIGHT - ypos - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
                glReadPixels(xpos, SCR_HEIGHT - ypos - 1, 1, 1, GL_RGB, GL_BYTE, &color);
                glReadPixels(xpos, SCR_HEIGHT - ypos - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
                float depthOffset = depth - lastDepth;
                lastDepth = depth;

                colorf[0] = color[0] / (float)127;
                colorf[1] = color[1] / (float)127;
                colorf[2] = color[2] / (float)127;

                shapeManager->processScalingIn3d(colorf, index - 1, 0.1 * (xoffset + yoffset), (10000) * -1 * depthOffset);
            }
            else {
                cout << "rotation" << endl;
  
                float dist = distance(lastX, lastY, xpos, ypos);
                cout << dist << " distance" << endl;
                if (dist > 0) {
                    glm::mat4 rogridRotation = virtualTrackball(lastX, lastY, xpos, ypos);
                    shapeManager->rotateIn3D(rogridRotation);
                }
            }
        }

        lastX = xpos;
        lastY = ypos;
    }
}
