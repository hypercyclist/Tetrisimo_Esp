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
    framesPerSeconds(30)
    // background(nullptr),
    // widget(nullptr)
{
    initializeStandartFunctions();
    childrens.resize(2);
}

Scene::~Scene()
{
}



// void Scene::render()
// {
//     // if (background != nullptr)
//     // {
//     //     background->draw();
//     // }
//     // if (widget != nullptr)
//     // {
//     //     widget->draw();
//     // }
// }

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
    // background = _background;
    // update();
    childrens[0] = _background;
    childrens[0]->update();
}

std::shared_ptr<Widget> Scene::getBackground()
{
    // return background;
    return childrens[0];
}

void Scene::setCentralWidget(std::shared_ptr<Widget> _widget)
{

    // widget = _widget;
    // widget->setSize(*size);
    // update();
    childrens[1] = _widget;
    childrens[1]->setSize(*size);
}

std::shared_ptr<Widget> Scene::getCentralWidget()
{
    // return widget;
    return childrens[1];
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
    Serial.println("Scene::update()");
    needUpdate = true;
    if (parent != nullptr)
    {
        parent->update();
    }
}

void Scene::initializeStandartFunctions()
{
    pressedButtonUpFunctionPointer = [this] () 
    {
        std::static_pointer_cast<VerticalLayout>(childrens[1])->focusPrevious();
    };
    pressedButtonDownFunctionPointer = [this] ()
    {
        std::static_pointer_cast<VerticalLayout>(childrens[1])->focusNext();
    };
    pressedButtonRightFunctionPointer = [this] () {};
    pressedButtonLeftFunctionPointer = [this] () {};
    pressedButtonOkFunctionPointer = [this] () 
    {
        std::static_pointer_cast<VerticalLayout>(childrens[1])->executeActiveWidget();
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
