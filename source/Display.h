#ifndef DISPLAY_H
#define DISPLAY_H

class Painter;
class Scene;
class Size;

#include <memory>

// This class describe display with his size and working pins.
class Display
{
    private:
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
        Display(
            Size _displaySize, 
            int _pinDisplayCS, 
            int _pinDisplayDC, 
            int _pinDisplayRST
        );
        ~Display();
        std::shared_ptr<Painter> getPainter();
        void setSize(Size _displaySize);
        Size getSize();
        std::shared_ptr<Scene> getActiveScene();
        void setActiveScene(std::shared_ptr<Scene> _activeScene);
};

#endif
