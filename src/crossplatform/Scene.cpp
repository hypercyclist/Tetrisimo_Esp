#include "Scene.h"

#include "Background.h"
#include "Color.h"
#include "Display.h"
#include "Label.h"
#include "Log.h"
#include "Game.h"
#include "Layout.h"
#include "Painter.h"
#include "Point.h"
#include "Size.h"
#include "VerticalLayout.h"

Scene::Scene(std::shared_ptr<Game> _game)
    : Widget(),
    game(_game),
    previousScene(nullptr),
    framesPerSeconds(30)
{
    initializeStandartFunctions();
    childrens.resize(2);
}

Scene::Scene(std::shared_ptr<Game> _game, 
    std::shared_ptr<Background> _background, std::string _headerText, 
    int _headerTextSize) : Scene(_game) 
{
    configureBasicMenuScene(_background, _headerText, _headerTextSize);
}

Scene::~Scene()
{
}

void Scene::configureBasicMenuScene(std::shared_ptr<Background> _background, 
    std::string _headerText, int _headerTextSize)
{
    setSize( game->getDisplay()->getSize() );
    setBackgroundWidget(_background);
    setCentralWidget(std::make_shared<VerticalLayout>());

    std::shared_ptr<Label> header = std::make_shared<Label>(_headerText);
    header->setTextSize(_headerTextSize);
    header->setUnderline(true);
    std::static_pointer_cast<VerticalLayout>(childrens[1])->addWidget(header);
}

std::shared_ptr<Scene> Scene::getPreviousScene()
{
    return previousScene;
}

void Scene::setPreviousScene(std::shared_ptr<Scene> _previousScene)
{
    previousScene = _previousScene;
}

void Scene::setBackgroundWidget(std::shared_ptr<Background> _background)
{
    // background = _background;
    // update();
    childrens[0] = _background;
    childrens[0]->setSize(*size);
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

void Scene::initializeStandartFunctions()
{
    onShowFunctionPointer = [this] () {};
    onHideFunctionPointer = [this] () 
    {
        std::static_pointer_cast<VerticalLayout>(childrens[1])->unfocus();
    };
    pressedButtonUpFunctionPointer = [this] () 
    {
        // std::static_pointer_cast<VerticalLayout>(childrens[1])->focusPrevious();
        std::static_pointer_cast<VerticalLayout>(childrens[1])->moveUp();
    };
    pressedButtonDownFunctionPointer = [this] ()
    {
        // std::static_pointer_cast<VerticalLayout>(childrens[1])->focusNext();
        std::static_pointer_cast<VerticalLayout>(childrens[1])->moveDown();
    };
    pressedButtonRightFunctionPointer = [this] () {};
    pressedButtonLeftFunctionPointer = [this] () {};
    pressedButtonOkFunctionPointer = [this] () 
    {
        std::static_pointer_cast<VerticalLayout>(childrens[1])->executeActiveWidget();
    };
    pressedButtonBackFunctionPointer = [this] () 
    {
        if (!previousScene) return;
        game->getDisplay()->setActiveScene(previousScene);
    };
}

void Scene::onShow()
{
    std::static_pointer_cast<VerticalLayout>(childrens[1])->countLayout();
    childrens[1]->focus();
    // Log::println("Scene::onShow - before onShowFunctionPointer", "LOW");
    onShowFunctionPointer();
    // Log::println("Scene::onShow - after onShowFunctionPointer", "LOW");
}

void Scene::setOnShowFunction(std::function<void()> _function)
{
    onShowFunctionPointer = _function;
}

void Scene::onHide()
{
    onHideFunctionPointer();
}

void Scene::setOnHideFunction(std::function<void()> _function)
{
    onHideFunctionPointer = _function;
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
