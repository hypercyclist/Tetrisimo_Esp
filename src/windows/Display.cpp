#include "Display.h"
#include "Config.h"
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

void framebufferSizeCallback(GLFWwindow* _window, int _width, int _height);

Display::Display(std::shared_ptr<Config> _config)
    : displaySize( std::make_shared<Size>(_config->getDisplaySize()) ),
    pinCS( _config->getPinDisplayCS() ),
    pinDC( _config->getPinDisplayDC() ),
    pinRST( _config->getPinDisplayRST() ),
    scale( _config->getDisplayScale() ),
    windowName("Tetrisimo")
{
    glfwInitConfigure();
    window = glfwCreateWindow(
        displaySize->getWidth() * scale, 
        displaySize->getHeight() * scale, 
        windowName.c_str(), NULL, NULL
    );
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    gladInitConfigure();
    camera = std::make_shared<Camera>();
    painter = std::make_shared<Painter>(_config, window, camera);
    Painter::setDefault(painter);
}

Display::~Display()
{
    glfwTerminate();
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

void Display::gladInitConfigure()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
    {
        Log::println("Failed to initialize GLAD", "HIGH");
    }
}

void framebufferSizeCallback(GLFWwindow* _window, int _width, int _height)
{
    glViewport(0, 0, _width, _height);
}

std::shared_ptr<Painter> Display::getPainter()
{
    return painter;
}

void Display::drawBuffer()
{
    painter->drawBuffer();
}

void Display::pollEvents()
{
    glfwPollEvents();
}

GLFWwindow* Display::getWindow()
{
    return window;
}

// void Display::setSize(Size _displaySize)
// {
//     displaySize = std::make_shared<Size>(_displaySize);
// }

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
