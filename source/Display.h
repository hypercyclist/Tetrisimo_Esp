#ifndef DISPLAY_H
#define DISPLAY_H

class Size;
class Painter;
class Scene;
#include <memory>

class Display
{
    private:
        std::shared_ptr<Size> displaySize;
        std::shared_ptr<Painter> painter;
        std::shared_ptr<Scene> activeScene;
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