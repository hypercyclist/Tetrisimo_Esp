#ifndef DISPLAY_H
#define DISPLAY_H

class Config;
class Painter;
class Scene;
class Size;

class GLFWwindow;
class Camera;
// class Pool;

#include <memory>
#include <string>

// This class describe display with his size and working pins.
class Display
{
    private:
        GLFWwindow* window;
        std::string windowName;
        std::shared_ptr<Camera> camera;
        std::shared_ptr<Size> displaySize;
        int scale;
        // Single only painter object create here.
        std::shared_ptr<Painter> painter;
        // Always point to current scene.
        std::shared_ptr<Scene> activeScene;
        // The pin numbers for physical display, welding things.
        int pinCS;
        int pinDC;
        int pinRST;
    public:
        Display(std::shared_ptr<Config> _config);
        ~Display();

        void glfwInitConfigure();
        void gladInitConfigure();
        std::shared_ptr<Painter> getPainter();
        void drawBuffer();
        void pollEvents();
        GLFWwindow* getWindow();
        // You can't just change size of display.
        // void setSize(Size _displaySize);
        Size getSize();
        std::shared_ptr<Scene> getActiveScene();
        void setActiveScene(std::shared_ptr<Scene> _activeScene);
};

#endif
