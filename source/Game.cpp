#include "Game.h"

#include "Size.h"
#include "Point.h"
#include "Config.h"
#include "KeyboardHook.h"
#include "Background.h"
#include "Scene.h"
#include "Label.h"
#include "VerticalLayout.h"
#include "Button.h"
#include "Resistor.h"
#include "PhysButton.h"
#include "Display.h"
#include "Painter.h"
#include "ResourceTheme.h"
#include "user_interface.h"
#include <SoftwareSerial.h>

// #include "IpAddress.h"
// #include "Port.h"
// #include "ServiceAddress.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::start()
{
    Serial.begin(115200);
    initialize();
    run();
}

void Game::initialize()
{
    initializeConfig();
    initializeButtons();
    initializeDisplay();

    display->getPainter()->setResourceTheme( config->getCaveLightsTheme() );

    initializeBackground();
    initializeMainMenu();
    initializeSettings();

    display->setActiveScene(mainMenu);
}

void Game::run()
{
    time_t roundTimeMs = 0;
    time_t lastInputTimeMs = 0;
    while (true)
    {
        roundTimeMs = getTimeMs();
        display->getActiveScene()->render();
        do
        {
            std::shared_ptr<PhysButton> pressedButton = keyboardHook->getPressedButton();
            if (pressedButton != nullptr)
            {
                if ( (getTimeMs() - lastInputTimeMs) > 200 )
                {
                    lastInputTimeMs = getTimeMs();
                    processPressedButton(pressedButton);
                    break;
                }
            }
            delay(5);
        }
        while ( (getTimeMs() - roundTimeMs) < display->getActiveScene()->getFrameTime() );
    }
}

time_t Game::getTimeMs()
{
    return (time_t)(system_get_time() / 1000);
}

void Game::processPressedButton(std::shared_ptr<PhysButton> _pressedButton)
{
    if (_pressedButton == buttonUp)
    {
        display->getActiveScene()->pressedButtonUp();
    }
    if (_pressedButton == buttonDown)
    {
        display->getActiveScene()->pressedButtonDown();
    }
    if (_pressedButton == buttonLeft)
    {
        // display->getActiveScene()->pressedButtonDown();
    }
    if (_pressedButton == buttonRight)
    {
        // display->getActiveScene()->pressedButtonDown();
    }
    if (_pressedButton == buttonOk)
    {
        display->getActiveScene()->pressedButtonOk();
    }
    if (_pressedButton == buttonBack)
    {
        // display->getActiveScene()->pressedButtonDown();
    }
}

void Game::initializeConfig()
{
    config = std::make_shared<Config>();
}

void Game::initializeButtons()
{
    buttonUp = std::make_shared<PhysButton>( config->getUpButtonResistor() );
    buttonDown = std::make_shared<PhysButton>( config->getDownButtonResistor() );
    buttonLeft = std::make_shared<PhysButton>( config->getLeftButtonResistor() );
    buttonRight = std::make_shared<PhysButton>( config->getRightButtonResistor() );
    buttonOk = std::make_shared<PhysButton>( config->getOkButtonResistor() );
    buttonBack = std::make_shared<PhysButton>( config->getBackButtonResistor() );

    keyboardHook = std::make_shared<KeyboardHook> ( KeyboardHook( config->getPinKeyboardAdc() ) );
    keyboardHook->addButton(buttonUp);
    keyboardHook->addButton(buttonDown);
    keyboardHook->addButton(buttonLeft);
    keyboardHook->addButton(buttonRight);
    keyboardHook->addButton(buttonOk);
    keyboardHook->addButton(buttonBack);
}

void Game::initializeDisplay()
{
    display = std::make_shared<Display>( 
        config->getDisplaySize(), 
        config->getPinDisplayCS(), 
        config->getPinDisplayDC(), 
        config->getPinDisplayRST() 
    );
}

void Game::initializeBackground()
{
    background = std::make_shared<Background>(nullptr);
    background->setSize( config->getDisplaySize() ); //bad
}

void Game::initializeMainMenu()
{
    mainMenu = std::make_shared<Scene>();
    mainMenu->setSize( display->getSize() );
    mainMenu->setBackgroundWidget(background);

    std::shared_ptr<VerticalLayout> menuLayout = std::make_shared<VerticalLayout>();
    mainMenu->setCentralWidget(menuLayout);

    std::shared_ptr<Label> header = std::make_shared<Label>("Тетрис");
    header->setTextSize(3);
    header->setUnderline(true);
    menuLayout->addWidget(header);

    std::shared_ptr<Button> singleGameButton = std::make_shared<Button>("Новая игра");
    menuLayout->addWidget(singleGameButton);

    std::shared_ptr<Button> multiplayerButton = std::make_shared<Button>("Сеть");
    menuLayout->addWidget(multiplayerButton);
    
    std::shared_ptr<Button> settingsButton = std::make_shared<Button>("Настройки");
    settingsButton->setExecuteFunction(
        [this] () 
        {
            display->setActiveScene(settings);
        }
    );
    menuLayout->addWidget(settingsButton);
    
    std::shared_ptr<Button> highScoreButton = std::make_shared<Button>("Рекорды");
    menuLayout->addWidget(highScoreButton);

    std::shared_ptr<Label> highScoreLabel = std::make_shared<Label>("000000");
    menuLayout->addWidget(highScoreLabel);

    singleGameButton->focus();
}

void Game::initializeSingleGame()
{

}

void Game::initializeMultiplayer()
{

}

void Game::initializeServerBrowser()
{

}

void Game::initializeCreateServer()
{

}

void Game::initializeCooperativeGame()
{

}

void Game::initializeVersusGame()
{

}

void Game::initializeSettings()
{
    settings = std::make_shared<Scene>();
    settings->setSize( display->getSize() );
    settings->setBackgroundWidget(background);

    std::shared_ptr<VerticalLayout> settingsLayout = std::make_shared<VerticalLayout>();
    settings->setCentralWidget(settingsLayout);

    std::shared_ptr<Label> header = std::make_shared<Label>("Настройки");
    header->setTextSize(2);
    header->setUnderline(true);
    settingsLayout->addWidget(header);

    std::shared_ptr<Button> gameSettingsButton = std::make_shared<Button>("Игровые");
    settingsLayout->addWidget(gameSettingsButton);

    std::shared_ptr<Button> networkSettingsButton = std::make_shared<Button>("Сетевые");
    settingsLayout->addWidget(networkSettingsButton);
    
    std::shared_ptr<Button> colorsSettingsButton = std::make_shared<Button>("Палитра");
    settingsLayout->addWidget(colorsSettingsButton);

    std::shared_ptr<Button> advancedSettingsButton = std::make_shared<Button>("Другие");
    settingsLayout->addWidget(advancedSettingsButton);
    
    std::shared_ptr<Label> aboutButton = std::make_shared<Label>("О проекте");
    settingsLayout->addWidget(aboutButton);
}

void Game::initializeGameSettings()
{

}

void Game::initializeNetworkSettings()
{

}

void Game::initializeAdvancedSettings()
{

}

void Game::initializeResistorSettings()
{

}

void Game::initializeColorsSettings()
{

}

void Game::initializeCustomColorsSettings()
{

}

void Game::initializeCustomFigureSettings()
{

}

void Game::initializeAboutSettings()
{

}
