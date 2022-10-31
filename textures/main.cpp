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

unsigned int loadTexture(const char* path);

// settings
TRANSFORMATION_MODE transformationMode = SCALE;
DIMENSION dimension = THREE;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool isUIClicked = false;
bool isMouseClicked = false;

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
            drawingPolygonManager->addThreeDimensionalFigure(new Cube());
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
        if (ImGui::Button("Scale")) {
            shapeManager->changeToScaleModeIn3d();
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
           
            glReadPixels(x, SCR_HEIGHT - y - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
           
            
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

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    GLbyte color[3];
    GLfloat colorf[3];
    GLuint index;
    GLfloat depth;

    if (isMouseClicked) {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (firstMouse)
        {
           
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

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
            glReadPixels(xpos, SCR_HEIGHT - ypos - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
            glReadPixels(xpos, SCR_HEIGHT - ypos - 1, 1, 1, GL_RGB, GL_BYTE, &color);
            glReadPixels(xpos, SCR_HEIGHT - ypos - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

            colorf[0] = color[0] / (float)127;
            colorf[1] = color[1] / (float)127;
            colorf[2] = color[2] / (float)127;
         
            cout << "xoffset "  << xoffset << endl;
            cout << "yoffest " << yoffset << endl;
            cout << "depth" << depth << endl;
            shapeManager->processScalingIn3d(colorf, index - 1, 0.3 * (xoffset + yoffset));
        }
    }
}
