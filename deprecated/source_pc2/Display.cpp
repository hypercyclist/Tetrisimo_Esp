#include "Display.h"
#include "Log.h"
#include "Size.h"
#include "Painter.h"
#include "Scene.h"

// #include "Pool.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"

#include <iostream>

Display::Display(
            Size _displaySize, 
            int _pinDisplayCS, 
            int _pinDisplayDC, 
            int _pinDisplayRST
            )
{
    std::cout << "displayStart" << std::endl;
    displaySize = std::make_shared<Size>(128, 160);
    std::cout << "after display size" << std::endl;
    pinDisplayCS = _pinDisplayCS;
    pinDisplayDC = _pinDisplayDC;
    pinDisplayRST = _pinDisplayRST;
    std::cout << "before init context" << std::endl;
    Log::println("Test1", "LOW");
    // initContext();
    painter = std::make_shared<Painter>();
    Painter::setDefault(painter);
    painter->setWindow(window);
    painter->setCamera(camera);
}

Display::~Display()
{
    glfwTerminate();
}

std::shared_ptr<Painter> Display::getPainter()
{
    return painter;
}

void Display::setSize(Size _displaySize)
{
    displaySize = std::make_shared<Size>(_displaySize);
}

Size Display::getSize()
{
    return *displaySize;
}

std::shared_ptr<Scene> Display::getActiveScene()
{
    return activeScene;
}

void Display::setActiveScene(std::shared_ptr<Scene> _activeScene)
{
    if (activeScene != nullptr)
    {
        activeScene->onHide();
    }
    activeScene = _activeScene;
    activeScene->onShow();
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Display::initContext()
{
    windowName = "Tetrisimo";
    std::cout << "a";
    camera = std::make_shared<Camera>();
    glfwInitConfigure();
    Log::println("Test2", "LOW");
    window = glfwCreateWindow(displaySize->getWidth(), displaySize->getHeight(), windowName.c_str(), NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    initGlad();
    Log::println("Test2", "LOW");
    camera->init();
    Log::println("Test3", "LOW");
}

void Display::glfwInitConfigure()
{
    std::cout << "b";
    if (glfwInit() != GLFW_TRUE) 
    { 
        Log::println("GLFW init failed", "LOW");
        glfwTerminate(); 
    }
    Log::println("Test2.1", "LOW");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Display::initGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Log::println("Failed to initialize GLAD", "HIGH");
    }
}

void Display::bindBuffers()
{

}

void Display::swapBuffers()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

// void Display::draw()
// {
//     glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     bindBuffers();
//     //glDrawArrays(GL_TRIANGLES, 0, 6);
//     glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//     glfwSwapBuffers(window);
//     glfwPollEvents();
// }

// void Display::moveCamera(float _x, float _y, float _z)
// {
//     camera.moveCamera(_x, _y, _z);
// }
