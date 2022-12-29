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

// game.h buttons to class;
// game.cpp display->getActiveScene to this->getActiveScene()
// game.cpp pressedButtonUp in scene wtf. to control class with initbuttons

// init scene with (config, background headerText, headerTextSize

// initializeStandartFunctions to game.

Game::Game()
{
}

Game::~Game()
{
}

void Game::start()
{
    initialize();
    run();
}

void Game::initialize()
{
    Log::init();
    initializeConfig();
    initializeDisplay();
    initializeButtons();

    display->getPainter()->setResourceTheme( config->getCaveLightsTheme() );

    initializeBackground();
    initializeWidgetViewer();
    initializeGameSettings();
    initializeColorsSettings();
    initializeResistorSettings();
    initializeAdvancedSettings();
    initializeAboutSettings();
    initializeMultiplayer();
    initializeSettings();
    initializeHighScore();
    initializeMainMenu();

    display->setActiveScene(mainMenu);
}

void Game::run()
{
    time_t roundTimeMs = 0;
    time_t lastInputTimeMs = 0;
    bool run = true;
    while (run)
    {
        roundTimeMs = PlatformTime::getTimeMs();
        display->getActiveScene()->render();
        display->drawBuffer();
        do
        {
            KeyboardKeys pressedButton = keyboardHook->getPressedButton();
            if (pressedButton != KeyboardKeys::NO_KEY)
            {
                if ( (PlatformTime::getTimeMs() - lastInputTimeMs) > 200 )
                {
                    lastInputTimeMs = PlatformTime::getTimeMs();
                    processPressedButton(pressedButton);
                    break;
                }
            }
            PlatformTime::delayTimeMs(5);
            display->pollEvents();
            // std::cout << PlatformTime::getTimeMs() - roundTimeMs << std::endl;
        }
        while ( (PlatformTime::getTimeMs() - roundTimeMs) < display->getActiveScene()->getFrameTime() );
    }
}

void Game::processPressedButton(KeyboardKeys _pressedButton)
{
    if (_pressedButton == KeyboardKeys::KEY_UP)
    {
        display->getActiveScene()->pressedButtonUp();
    }
    if (_pressedButton == KeyboardKeys::KEY_DOWN)
    {
        display->getActiveScene()->pressedButtonDown();
    }
    if (_pressedButton == KeyboardKeys::KEY_LEFT)
    {
        display->getActiveScene()->pressedButtonLeft();
    }
    if (_pressedButton == KeyboardKeys::KEY_RIGHT)
    {
        display->getActiveScene()->pressedButtonRight();
    }
    if (_pressedButton == KeyboardKeys::KEY_OK)
    {
        display->getActiveScene()->pressedButtonOk();
    }
    if (_pressedButton == KeyboardKeys::KEY_BACK)
    {
        display->getActiveScene()->pressedButtonBack();
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

void Game::initializeButtons()
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
