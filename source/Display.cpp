#include "Display.h"
#include "Size.h"
#include "Painter.h"
#include "Scene.h"

Display::Display(
            Size _displaySize, 
            int _pinDisplayCS, 
            int _pinDisplayDC, 
            int _pinDisplayRST
            )
    : activeScene(nullptr)
{
    displaySize = std::make_shared<Size>(_displaySize);
    pinDisplayCS = _pinDisplayCS;
    pinDisplayDC = _pinDisplayDC;
    pinDisplayRST = _pinDisplayRST;
    painter = std::make_shared<Painter>(
        _pinDisplayCS,
        _pinDisplayDC,
        _pinDisplayRST
        );
    Painter::setDefault(painter);
}

Display::~Display()
{
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
    activeScene = _activeScene;
    // activeScene->setSize(*displaySize);
    activeScene->getCentralWidget()->focus();
    activeScene->updateAll();
    // activeScene->redraw();
}