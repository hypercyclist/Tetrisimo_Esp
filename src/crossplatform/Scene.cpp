#include "Scene.h"

#include "Background.h"
#include "Color.h"
#include "Display.h"
#include "KeyboardHook.h"
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
    childrens.resize(2, nullptr);
}

Scene::Scene(std::shared_ptr<Game> _game, 
    std::shared_ptr<Background> _background, std::string _headerText, 
    int _headerTextSize) : 
    Scene(_game) 
{
    configureBasicMenuScene(_background, _headerText, _headerTextSize);
}

Scene::~Scene() { }

void Scene::render()
{
    background->render();
    widget->render();
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
    std::static_pointer_cast<VerticalLayout>(widget)->addWidget(header);
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
    background = _background;
    background->setSize(*size);
}

std::shared_ptr<Widget> Scene::getBackground()
{
    return background;
}

void Scene::setCentralWidget(std::shared_ptr<Widget> _widget)
{
    widget = _widget;
    widget->setSize(*size);
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

void Scene::initializeStandartFunctions()
{
    onShowFunctionPointer = [this] () 
    {
        std::static_pointer_cast<VerticalLayout>(widget)->countLayout();
        widget->focus();
    };
    onHideFunctionPointer = [this] () 
    {
        std::static_pointer_cast<VerticalLayout>(widget)->unfocus();
    };
    pressedButtonUpFunctionPointer = [this] () 
    {
        // std::static_pointer_cast<VerticalLayout>(widget)->focusPrevious();
        std::static_pointer_cast<VerticalLayout>(widget)->moveUp();
    };
    pressedButtonDownFunctionPointer = [this] ()
    {
        // std::static_pointer_cast<VerticalLayout>(widget)->focusNext();
        std::static_pointer_cast<VerticalLayout>(widget)->moveDown();
    };
    pressedButtonRightFunctionPointer = [this] () {};
    pressedButtonLeftFunctionPointer = [this] () {};
    pressedButtonOkFunctionPointer = [this] () 
    {
        std::static_pointer_cast<VerticalLayout>(widget)->executeActiveWidget();
    };
    pressedButtonBackFunctionPointer = [this] () 
    {
        if (!previousScene) return;
        game->setActiveScene(previousScene);
    };
}

void Scene::processKeyboard(KeyboardKeys _pressedButton)
{
    if (_pressedButton == KeyboardKeys::KEY_UP) pressedButtonUp();
    if (_pressedButton == KeyboardKeys::KEY_DOWN) pressedButtonDown();
    if (_pressedButton == KeyboardKeys::KEY_LEFT) pressedButtonLeft();
    if (_pressedButton == KeyboardKeys::KEY_RIGHT) pressedButtonRight();
    if (_pressedButton == KeyboardKeys::KEY_OK) pressedButtonOk();
    if (_pressedButton == KeyboardKeys::KEY_BACK) pressedButtonBack();
}

void Scene::setOnShowFunction(std::function<void()> _function) {
    onShowFunctionPointer = _function;
}

void Scene::setOnHideFunction(std::function<void()> _function) {
    onHideFunctionPointer = _function;
}

void Scene::setPressedButtonUpFunction(std::function<void()> _function) {
    pressedButtonUpFunctionPointer = _function;
}

void Scene::setPressedButtonDownFunction(std::function<void()> _function) {
    pressedButtonDownFunctionPointer = _function;
}

void Scene::setPressedButtonLeftFunction(std::function<void()> _function) {
    pressedButtonLeftFunctionPointer = _function;
}

void Scene::setPressedButtonRightFunction(std::function<void()> _function) {
    pressedButtonRightFunctionPointer = _function;
}

void Scene::setPressedButtonOkFunction(std::function<void()> _function) {
    pressedButtonOkFunctionPointer = _function;
}

void Scene::setPressedButtonBackFunction(std::function<void()> _function) {
    pressedButtonBackFunctionPointer = _function;
}

void Scene::onShow() { onShowFunctionPointer(); }
void Scene::onHide() { onHideFunctionPointer(); }
void Scene::pressedButtonUp() { pressedButtonUpFunctionPointer(); }
void Scene::pressedButtonDown() { pressedButtonDownFunctionPointer(); }
void Scene::pressedButtonLeft() { pressedButtonLeftFunctionPointer(); }
void Scene::pressedButtonRight() { pressedButtonRightFunctionPointer(); }
void Scene::pressedButtonOk() { pressedButtonOkFunctionPointer(); }
void Scene::pressedButtonBack() { pressedButtonBackFunctionPointer(); }
