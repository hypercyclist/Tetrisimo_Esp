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
#include "Layout.h"

Scene::Scene(std::shared_ptr<Game> _game)
    : Widget(),
    game(_game),
    previousScene(nullptr),
    framesPerSeconds(30)
{
    initializeStandartFunctions();
    setSize( game->getDisplay()->getSize() );
}

Scene::~Scene() { }

void Scene::render()
{
    background->render();
    getLayout()->render();
}

void Scene::configureBasicMenuScene(std::shared_ptr<Background> _background, 
    std::string _headerText, int _headerTextSize)
{
    setBackgroundWidget(_background);

    std::shared_ptr<Label> header = std::make_shared<Label>(_headerText);
    header->setTextSize(_headerTextSize);
    header->setUnderline(true);
    getLayout()->addWidget(header);
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
        getLayout()->countLayout();
        getLayout()->focus();
    };
    onHideFunctionPointer = [this] () 
    {
        getLayout()->unfocus();
    };
    pressedButtonUpFunctionPointer = [this] () 
    {
        // getLayout()->focusPrevious();
        getLayout()->moveUp();
    };
    pressedButtonDownFunctionPointer = [this] ()
    {
        // getLayout()->focusNext();
        getLayout()->moveDown();
    };
    pressedButtonRightFunctionPointer = [this] () {};
    pressedButtonLeftFunctionPointer = [this] () {};
    pressedButtonOkFunctionPointer = [this] () 
    {
        getLayout()->executeActiveWidget();
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
