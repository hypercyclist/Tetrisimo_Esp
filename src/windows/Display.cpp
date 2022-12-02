#include "Display.h"
#include "Log.h"
#include "Size.h"
#include "Painter.h"
#include "Scene.h"

// #include "Pool.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
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
    displaySize = std::make_shared<Size>(_displaySize);
    pinDisplayCS = _pinDisplayCS;
    pinDisplayDC = _pinDisplayDC;
    pinDisplayRST = _pinDisplayRST;
    initContext();
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
    camera = std::make_shared<Camera>();
    glfwInitConfigure();
    window = glfwCreateWindow(displaySize->getWidth(), displaySize->getHeight(), windowName.c_str(), NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    initGlad();
    camera->init();
}

void Display::glfwInitConfigure()
{
    if (glfwInit() != GLFW_TRUE) 
    { 
        Log::println("GLFW init failed", "LOW");
        glfwTerminate(); 
    }
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
