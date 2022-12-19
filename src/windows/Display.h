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
        // Pool* pool;
        // Camera camera;
        std::shared_ptr<Size> displaySize;
        // Single only painter object create here.
        std::shared_ptr<Painter> painter;
        // Always point to current scene.
        std::shared_ptr<Scene> activeScene;
        // The pin numbers for physical display, welding things.
        int pinDisplayCS;
        int pinDisplayDC;
        int pinDisplayRST;
    public:
        Display(std::shared_ptr<Config> _config);
        ~Display();

        // void draw();
        void initContext();
        void glfwInitConfigure();
        void initGlad();
        void bindBuffers();
        void swapBuffers();

        std::shared_ptr<Painter> getPainter();
        void setSize(Size _displaySize);
        Size getSize();
        int displayScale;
        std::shared_ptr<Scene> getActiveScene();
        void setActiveScene(std::shared_ptr<Scene> _activeScene);
};

#endif
