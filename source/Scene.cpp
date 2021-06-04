#include "Scene.h"
#include "Game.h"
#include "Display.h"
#include "Painter.h"
#include "Color.h"
#include "Point.h"
#include "Size.h"
#include "Background.h"
#include "Layout.h"
#include "VerticalLayout.h"

#include <SoftwareSerial.h>

Scene::Scene(std::shared_ptr<Game> _game)
    : 
    Widget(),
    game(_game),
    previousScene(nullptr),
    framesPerSeconds(30),
    background(nullptr),
    widget(nullptr)
{
    initializeStandartFunctions();
}

Scene::~Scene()
{
}



void Scene::render()
{
    if (background != nullptr)
    {
        background->draw();
    }
    if (widget != nullptr)
    {
        widget->draw();
    }
}

void Scene::updateAll()
{
    if (background != nullptr)
    {
        background->render();
    }
    if (widget != nullptr)
    {
        widget->render();
    }
}

// void Scene::processChild(std::shared_ptr<Widget> _childWidget)
// {
//     setCentralWidget(_childWidget);
// }



std::shared_ptr<Scene> Scene::getPreviousScene()
{
    return previousScene;
}

void Scene::setPreviousScene(std::shared_ptr<Scene> _previousScene)
{
    previousScene = _previousScene;
    _previousScene->update();
}

void Scene::setBackgroundWidget(std::shared_ptr<Background> _background)
{
    background = _background;
    update();
}    

void Scene::setCentralWidget(std::shared_ptr<Widget> _widget)
{
    widget = _widget;
    widget->setSize(*size);
    update();
}

std::shared_ptr<Widget> Scene::getCentralWidget()
{
    return widget;
}

int Scene::getFrameTime()
{
    return 1000 / framesPerSeconds;
}

void Scene::setFrameTime(int _framesPerSeconds)
{
    framesPerSeconds = _framesPerSeconds;
}

void Scene::update()
{
    needUpdate = true;
    if (background != nullptr)
    {
        background->update();
    }
}

void Scene::initializeStandartFunctions()
{
    pressedButtonUpFunctionPointer = [this] () 
    {
        std::static_pointer_cast<VerticalLayout>(widget)->focusPrevious();
    };
    pressedButtonDownFunctionPointer = [this] ()
    {
        std::static_pointer_cast<VerticalLayout>(widget)->focusNext();
    };
    pressedButtonRightFunctionPointer = [this] () {};
    pressedButtonLeftFunctionPointer = [this] () {};
    pressedButtonOkFunctionPointer = [this] () 
    {
        std::static_pointer_cast<VerticalLayout>(widget)->executeActiveWidget();
    };
    pressedButtonBackFunctionPointer = [this] () 
    {
        game->getDisplay()->setActiveScene(previousScene);
    };
}

void Scene::pressedButtonUp()
{
    pressedButtonUpFunctionPointer();
}

void Scene::setPressedButtonUpFunction(std::function<void()> _function)
{
    pressedButtonUpFunctionPointer = _function;
}

void Scene::pressedButtonDown()
{
    pressedButtonDownFunctionPointer();
}

void Scene::setPressedButtonDownFunction(std::function<void()> _function)
{
    pressedButtonDownFunctionPointer = _function;
}

void Scene::pressedButtonLeft()
{
    pressedButtonLeftFunctionPointer();
}

void Scene::setPressedButtonLeftFunction(std::function<void()> _function)
{
    pressedButtonLeftFunctionPointer = _function;
}

void Scene::pressedButtonRight()
{
    pressedButtonRightFunctionPointer();
}

void Scene::setPressedButtonRightFunction(std::function<void()> _function)
{
    pressedButtonRightFunctionPointer = _function;
}

void Scene::pressedButtonOk()
{
    pressedButtonOkFunctionPointer();
}

void Scene::setPressedButtonOkFunction(std::function<void()> _function)
{
    pressedButtonOkFunctionPointer = _function;
}

void Scene::pressedButtonBack()
{
    pressedButtonBackFunctionPointer();
}

void Scene::setPressedButtonBackFunction(std::function<void()> _function)
{
    pressedButtonBackFunctionPointer = _function;
}
