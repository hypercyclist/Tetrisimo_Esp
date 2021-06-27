#include "Game.h"

#include "Background.h"
#include "Button.h"
#include "CheckBox.h"
#include "Config.h"
#include "Display.h"
#include "KeyboardHook.h"
#include "Label.h"
#include "Painter.h"
#include "PhysButton.h"
#include "Point.h"
#include "Resistor.h"
#include "ResourceTheme.h"
#include "Size.h"
#include "Scene.h"
#include "TableView.h"
#include "TextView.h"
#include "user_interface.h"
#include "VerticalLayout.h"

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
    initializeGameSettings();
    initializeAboutSettings();
    initializeMultiplayer();
    initializeSettings();
    initializeHighScore();
    initializeMainMenu();

    display->setActiveScene(aboutSettings);
}

void Game::run()
{
    time_t roundTimeMs = 0;
    time_t lastInputTimeMs = 0;
    while (true)
    {
        roundTimeMs = getTimeMs();
        display->getActiveScene()->traverse();
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
        display->getActiveScene()->pressedButtonBack();
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
    background = std::make_shared<Background>();
    background->setSize( display->getSize() );
}

void Game::initializeBasicScene(
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

void Game::initializeMainMenu()
{
    mainMenu = std::make_shared<Scene>( shared_from_this() );
    initializeBasicScene(mainMenu, "Тетрис", 3);
    std::shared_ptr<VerticalLayout> menuLayout = 
        std::static_pointer_cast<VerticalLayout>( mainMenu->getCentralWidget() );
    menuLayout->setAdjusting(true);

    std::shared_ptr<Button> singleGameButton = std::make_shared<Button>("Новая игра");
    menuLayout->addWidget(singleGameButton);

    std::shared_ptr<Button> multiplayerButton = std::make_shared<Button>("Сеть");
    menuLayout->addWidget(multiplayerButton);
    multiplayerButton->setExecuteFunction(
        [this] ()
        {
            display->setActiveScene(multiplayer);
        }
    );
    multiplayer->setPreviousScene(mainMenu);
    
    std::shared_ptr<Button> settingsButton = std::make_shared<Button>("Настройки");
    menuLayout->addWidget(settingsButton);
    settingsButton->setExecuteFunction(
        [this] ()
        {
            display->setActiveScene(settings);
        }
    );
    settings->setPreviousScene(mainMenu);
    
    std::shared_ptr<Button> highScoreButton = std::make_shared<Button>("Рекорды");
    menuLayout->addWidget(highScoreButton);
    highScoreButton->setExecuteFunction(
        [this] ()
        {
            display->setActiveScene(highScore);
        }
    );
    highScore->setPreviousScene(mainMenu);

    std::shared_ptr<Label> highScoreLabel = std::make_shared<Label>("000000");
    menuLayout->addWidget(highScoreLabel);
}

void Game::initializeSingleGame()
{

}

void Game::initializeMultiplayer()
{
    multiplayer = std::make_shared<Scene>( shared_from_this() );
    initializeBasicScene(multiplayer, "Сеть", 2);
    std::shared_ptr<VerticalLayout> multiplayerLayout = 
        std::static_pointer_cast<VerticalLayout>( multiplayer->getCentralWidget() );

    std::shared_ptr<Button> clientButton = std::make_shared<Button>("Я клиент");
    multiplayerLayout->addWidget(clientButton);

    std::shared_ptr<Button> hostButton = std::make_shared<Button>("Я сервер");
    multiplayerLayout->addWidget(hostButton);
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
    settings = std::make_shared<Scene>( shared_from_this() );
    initializeBasicScene(settings, "Настройки", 2);
    std::shared_ptr<VerticalLayout> settingsLayout = 
        std::static_pointer_cast<VerticalLayout>( settings->getCentralWidget() );

    std::shared_ptr<Button> gameSettingsButton = std::make_shared<Button>("Игровые");
    settingsLayout->addWidget(gameSettingsButton);
    gameSettingsButton->setExecuteFunction(
        [this] ()
        {
            display->setActiveScene(gameSettings);
        }
    );
    gameSettings->setPreviousScene(settings);

    std::shared_ptr<Button> networkSettingsButton = std::make_shared<Button>("Сетевые");
    settingsLayout->addWidget(networkSettingsButton);
    
    std::shared_ptr<Button> colorsSettingsButton = std::make_shared<Button>("Палитра");
    settingsLayout->addWidget(colorsSettingsButton);

    std::shared_ptr<Button> advancedSettingsButton = std::make_shared<Button>("Другие");
    settingsLayout->addWidget(advancedSettingsButton);
    
    std::shared_ptr<Button> aboutButton = std::make_shared<Button>("О проекте");
    settingsLayout->addWidget(aboutButton);
    aboutButton->setExecuteFunction(
        [this] ()
        {
            display->setActiveScene(aboutSettings);
        }
    );
    aboutSettings->setPreviousScene(settings);
}

void Game::initializeGameSettings()
{
    gameSettings = std::make_shared<Scene>( shared_from_this() );
    initializeBasicScene(gameSettings, "Настройки", 2);
    std::shared_ptr<VerticalLayout> gameSettingsLayout = 
        std::static_pointer_cast<VerticalLayout>( gameSettings->getCentralWidget() );

    std::shared_ptr<CheckBox> useNetButton = std::make_shared<CheckBox>("Сетка", true);
    gameSettingsLayout->addWidget(useNetButton);
    useNetButton->setExecuteFunction(
        [this, useNetButton] ()
        {
            useNetButton->setState( !useNetButton->getState() );
            useNetButton->updateOne();
        }
    );

    std::shared_ptr<CheckBox> useGhostButton = std::make_shared<CheckBox>("Тень", true);
    gameSettingsLayout->addWidget(useGhostButton);
    useGhostButton->setExecuteFunction(
        [this, useGhostButton] ()
        {
            useGhostButton->setState( !useGhostButton->getState() );
            useGhostButton->updateOne();
        }
    );

    std::shared_ptr<CheckBox> useVibrationButton = std::make_shared<CheckBox>("Вибро", true);
    gameSettingsLayout->addWidget(useVibrationButton);
    useVibrationButton->setExecuteFunction(
        [this, useVibrationButton] ()
        {
            useVibrationButton->setState( !useVibrationButton->getState() );
            useVibrationButton->updateOne();
        }
    );
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
    aboutSettings = std::make_shared<Scene>( shared_from_this() );
    initializeBasicScene(aboutSettings, "О проекте", 2);
    std::shared_ptr<VerticalLayout> aboutSettingsLayout = 
        std::static_pointer_cast<VerticalLayout>( aboutSettings->getCentralWidget() );

    std::shared_ptr<TextView> thanksTable = std::make_shared<TextView>
        ("Спасибо!", "Всем товарищам, чьи имена я скрыл для этого скриншота!"); 
    //Никите, Льву, Анастасии, Дмитрию, Игорю, Александру, Александре.
    aboutSettingsLayout->addWidget(thanksTable);
    std::shared_ptr<TextView> contactsTable = std::make_shared<TextView>
        ("Контакты", "warstar441@gmail.com");
    aboutSettingsLayout->addWidget(contactsTable);
    // thanksTable->setExecuteFunction(
    //     [this, thanksTable] ()
    //     {
    //     }
    // );
}

void Game::initiazlieKeyboard()
{

}

void Game::initializeHighScore()
{
    highScore = std::make_shared<Scene>( shared_from_this() );
    initializeBasicScene(highScore, "Рекорды", 2);
    std::shared_ptr<VerticalLayout> highScoreLayout = 
        std::static_pointer_cast<VerticalLayout>( highScore->getCentralWidget() );

    std::shared_ptr<TableView> personalBest = std::make_shared<TableView>
        ("Мои рекорды", "1. Yuki...10 000");
    //Никите, Льву, Анастасии, Дмитрию, Игорю, Александру, Александре.
    highScoreLayout->addWidget(personalBest);
}

std::shared_ptr<Display> Game::getDisplay()
{
    return display;
}
