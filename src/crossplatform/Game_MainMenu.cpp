#include "Game.h"

// #include "Background.h"
#include "Button.h"
// #include "CheckBox.h"
// #include "Config.h"
#include "Display.h"
// #include "KeyboardHook.h"
#include "Label.h"
// #include "LineEdit.h"
// #include "PaletteView.h"
// #include "PhysButton.h"
// #include "Point.h"
// #include "Resistor.h"
// #include "ResourceTheme.h"
// #include "Size.h"
#include "Scene.h"
// #include "TableView.h"
// #include "TextView.h"
#include "Layout.h"


// #include "Color.h"

void Game::initializeMainMenu()
{
    mainMenu = std::make_shared<Scene>( shared_from_this());
    mainMenu->configureBasicMenuScene(background, "Тетрис", 3);

    std::shared_ptr<Button> singleGameButton = std::make_shared<Button>("Новая игра");
    mainMenu->getLayout()->addWidget(singleGameButton);

    std::shared_ptr<Button> multiplayerButton = std::make_shared<Button>("Сеть");
    mainMenu->getLayout()->addWidget(multiplayerButton);
    multiplayerButton->setExecuteFunction(
        [this] ()
        {
            setActiveScene(multiplayer);
        }
    );
    multiplayer->setPreviousScene(mainMenu);
    
    std::shared_ptr<Button> settingsButton = std::make_shared<Button>("Настройки");
    mainMenu->getLayout()->addWidget(settingsButton);
    settingsButton->setExecuteFunction(
        [this] ()
        {
            setActiveScene(settings);
        }
    );
    settings->setPreviousScene(mainMenu);
    
    std::shared_ptr<Button> highScoreButton = std::make_shared<Button>("Рекорды");
    mainMenu->getLayout()->addWidget(highScoreButton);
    highScoreButton->setExecuteFunction(
        [this] ()
        {
            setActiveScene(highScore);
        }
    );
    highScore->setPreviousScene(mainMenu);

    // std::shared_ptr<Button> desk1 = std::make_shared<Button>("Заглушка1");
    // mainMenu->getLayout()->addWidget(desk1);

    // std::shared_ptr<Button> desk2 = std::make_shared<Button>("Заглушка2");
    // mainMenu->getLayout()->addWidget(desk2);

    // std::shared_ptr<Button> desk3 = std::make_shared<Button>("Заглушка3");
    // mainMenu->getLayout()->addWidget(desk3);

    // std::shared_ptr<Button> desk4 = std::make_shared<Button>("Заглушка4");
    // mainMenu->getLayout()->addWidget(desk4);

    std::shared_ptr<Label> highScoreLabel = std::make_shared<Label>("000000");
    mainMenu->getLayout()->addWidget(highScoreLabel);
}
