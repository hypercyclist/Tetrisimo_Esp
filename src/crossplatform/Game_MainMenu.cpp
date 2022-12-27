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
#include "VerticalLayout.h"


// #include "Color.h"

void Game::initializeMainMenu()
{
    mainMenu = std::make_shared<Scene>( shared_from_this() );
    configureBasicMenuScene(mainMenu, "Тетрис", 3);
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
    // multiplayer->setPreviousScene(mainMenu);
    
    std::shared_ptr<Button> settingsButton = std::make_shared<Button>("Настройки");
    menuLayout->addWidget(settingsButton);
    settingsButton->setExecuteFunction(
        [this] ()
        {
            display->setActiveScene(settings);
        }
    );
    // settings->setPreviousScene(mainMenu);
    
    std::shared_ptr<Button> highScoreButton = std::make_shared<Button>("Рекорды");
    menuLayout->addWidget(highScoreButton);
    highScoreButton->setExecuteFunction(
        [this] ()
        {
            display->setActiveScene(highScore);
        }
    );
    // highScore->setPreviousScene(mainMenu);

    // std::shared_ptr<Button> desk1 = std::make_shared<Button>("Заглушка1");
    // menuLayout->addWidget(desk1);

    // std::shared_ptr<Button> desk2 = std::make_shared<Button>("Заглушка2");
    // menuLayout->addWidget(desk2);

    // std::shared_ptr<Button> desk3 = std::make_shared<Button>("Заглушка3");
    // menuLayout->addWidget(desk3);

    // std::shared_ptr<Button> desk4 = std::make_shared<Button>("Заглушка4");
    // menuLayout->addWidget(desk4);

    std::shared_ptr<Label> highScoreLabel = std::make_shared<Label>("000000");
    menuLayout->addWidget(highScoreLabel);
}
