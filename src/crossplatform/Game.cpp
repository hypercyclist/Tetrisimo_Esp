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

// пацан слово дал, и если надо, он его забрал!!!
// game.h std::shared_ptr scenes to unique_ptr;
// game.h buttons to class;
// game.cpp display->getActiveScene to this->getActiveScene()
// game.cpp pressedButtonUp in scene wtf. to control class with initbuttons

// init display with config in parameters.

// init background without setSize. do it automaticaly.

// init scene with (config, background headerText, headerTextSize

// initializeStandartFunctions to game.

// onButtonBack
//   activeScene->executeFunction(

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
    // initializeGameSettings();
    // initializeColorsSettings();
    // initializeResistorSettings();
    // initializeAdvancedSettings();
    // initializeAboutSettings();
    // initializeMultiplayer();
    // initializeSettings();
    // initializeHighScore();
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
    background->setSize( display->getSize() );
}

void Game::configureBasicMenuScene(
    std::shared_ptr<Scene> _scene, 
    std::string _headerText, 
    int _headerTextSize
    )
{
    _scene->setSize( display->getSize() );
    _scene->setBackgroundWidget(background);

    std::shared_ptr<VerticalLayout> menuLayout = std::make_shared<VerticalLayout>();
    _scene->setCentralWidget(menuLayout);

    std::shared_ptr<Label> header = std::make_shared<Label>(_headerText);
    header->setTextSize(_headerTextSize);
    header->setUnderline(true);
    menuLayout->addWidget(header);
}

std::shared_ptr<Display> Game::getDisplay()
{
    return display;
}

    // Painter* pPainter = display->getPainter().get();
    // pPainter->fillRect(0, 0, 128, 160, pPainter->getResourceTheme()->getUnfocusColor().toUint16());
    // pPainter->setTextSize(3);
    // pPainter->setPaintColor(pPainter->getResourceTheme()->getFocusColor());
    // pPainter->paintText("Новая игра", Point(10, 10));
    // pPainter->drawBuffer();

    // display->getPainter()->paintRect(0, 0, 5, 5, colorWhite);
    // display->getPainter()->paintRect(5, 5, 10, 10, colorBlack);

    // painter->drawText(10, 10, "abcdefghijklmn", painter->getResourceTheme()->getFocusColor().toUint16(), 1);
    // painter->drawText(10, 20, "opqrstuvwxyz", painter->getResourceTheme()->getFocusColor().toUint16(), 1);
    // painter->drawText(10, 30, "абвгдежзиклмн", painter->getResourceTheme()->getFocusColor().toUint16(), 1);
    // painter->drawText(10, 40, "опрстуххчщыьъюя", painter->getResourceTheme()->getFocusColor().toUint16(), 1);
    // painter->drawText(10, 50, "ABCDEFGHIJKLMN", painter->getResourceTheme()->getFocusColor().toUint16(), 1);
    // painter->drawText(10, 60, "OPQRSTUVWXYZ", painter->getResourceTheme()->getFocusColor().toUint16(), 1);
    // painter->drawText(10, 70, "АБВГДЕЖЗИКЛМН", painter->getResourceTheme()->getFocusColor().toUint16(), 1);
    // painter->drawText(10, 80, "ОПРСТУХХЧЩЬЪЭЮЯ", painter->getResourceTheme()->getFocusColor().toUint16(), 1);
    // painter->drawText(10, 90, "123456789-!.,/)", painter->getResourceTheme()->getFocusColor().toUint16(), 1);
    // painter->testFont(0);