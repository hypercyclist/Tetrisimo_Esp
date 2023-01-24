#include "Game.h"

#include "Background.h"
#include "Button.h"
#include "CheckBox.h"
#include "Config.h"
#include "Display.h"
#include "KeyboardHook.h"
#include "Label.h"
#include "LineEdit.h"
#include "Painter.h"
#include "PaletteView.h"
#include "PhysButton.h"
#include "Point.h"
#include "Resistor.h"
#include "ResourceTheme.h"
#include "Size.h"
#include "Scene.h"
#include "TableView.h"
#include "TextView.h"
#include "PlatformTime.h"
#include "VerticalLayout.h"

#include "Log.h"

#include "Color.h"

#include <iostream>

// #include "IpAddress.h"
// #include "Port.h"
// #include "ServiceAddress.h"

Game::Game() 
    : gameRunning(false)
{ }

Game::~Game() { }

void Game::start()
{
    initialize();
    run();
}

void Game::stop()
{
    bool gameRunning = false;
}

void Game::initialize()
{
    Log::init();
    initializeConfig();
    initializeDisplay();
    initializeKeyboardHook();

    display->getPainter()->setResourceTheme( config->getCaveLightsTheme() );

    initializeBackground();
    initializeWidgetViewer();
    initializeGameSettings();
    initializeColorsSettings();
    // initializeResistorSettings();
    initializeAdvancedSettings();
    initializeAboutSettings();
    initializeMultiplayer();
    initializeSettings();
    initializeHighScore();
    initializeMainMenu();

    setActiveScene(mainMenu);
}

void Game::run()
{
    gameRunning = true;
    while (gameRunning)
    {
        PlatformTime::updateTime();
        activeScene->render();
        display->drawBuffer();
        do
        {
            PlatformTime::sleepTimeMs(5);
            processKeyboard();
            display->pollEvents();
        }
        while (PlatformTime::getDeltaTimeMs() < activeScene->getFrameTime());
    }
}

void Game::processKeyboard()
{
    KeyboardKeys pressedButton = keyboardHook->getPressedButton();
    if (pressedButton != KeyboardKeys::NO_KEY)
    {
        activeScene->processKeyboard(pressedButton);
    }
}

void Game::initializeConfig()
{
    config = std::make_shared<Config>();
}

void Game::initializeDisplay()
{
    display = std::make_shared<Display>(config);
}

void Game::initializeKeyboardHook()
{
    keyboardHook = std::make_shared<KeyboardHook> (config, display);
}

void Game::initializeBackground()
{
    background = std::make_shared<Background>();
}

std::shared_ptr<Display> Game::getDisplay()
{
    return display;
}

std::shared_ptr<Scene> Game::getActiveScene()
{
    return activeScene;
}

void Game::setActiveScene(std::shared_ptr<Scene> _activeScene)
{
    if (activeScene != nullptr)
    {
        activeScene->onHide();
    }
    activeScene = _activeScene;
    activeScene->onShow();
}