#include "Game.h"

// #include "Background.h"
#include "Button.h"
// #include "CheckBox.h"
// #include "Config.h"
#include "Display.h"
// #include "KeyboardHook.h"
// #include "Label.h"
// #include "LineEdit.h"
#include "Painter.h"
// #include "PaletteView.h"
// #include "PhysButton.h"
// #include "Point.h"
// #include "Resistor.h"
// #include "ResourceTheme.h"
// #include "Size.h"
#include "Scene.h"
// #include "TableView.h"
// #include "TextView.h"
// #include "DefineTime.h"
#include "Layout.h"

// #include "Log.h"

// #include "Color.h"

void Game::initializeSettings()
{
    settings = std::make_shared<Scene>( shared_from_this(), background, "Настройки", 2);
    std::shared_ptr<Layout> settingsLayout = 
        std::static_pointer_cast<Layout>( settings->getCentralWidget() );

    std::shared_ptr<Button> gameSettingsButton = std::make_shared<Button>("Игровые");
    settingsLayout->addWidget(gameSettingsButton);
    gameSettingsButton->setExecuteFunction(
        [this] ()
        {
            setActiveScene(gameSettings);
        }
    );
    gameSettings->setPreviousScene(settings);

    std::shared_ptr<Button> networkSettingsButton = std::make_shared<Button>("Сетевые");
    settingsLayout->addWidget(networkSettingsButton);
    
    std::shared_ptr<Button> colorsSettingsButton = std::make_shared<Button>("Палитра");
    settingsLayout->addWidget(colorsSettingsButton);
    colorsSettingsButton->setExecuteFunction(
        [this] ()
        {
            setActiveScene(colorsSettings);
        }
    );
    colorsSettings->setPreviousScene(settings);

    std::shared_ptr<Button> advancedSettingsButton = std::make_shared<Button>("Другие");
    settingsLayout->addWidget(advancedSettingsButton); 
    advancedSettingsButton->setExecuteFunction(
        [this] ()
        {
            setActiveScene(advansedSettings);
        }
    );
    advansedSettings->setPreviousScene(settings);

    std::shared_ptr<Button> aboutButton = std::make_shared<Button>("О проекте");
    settingsLayout->addWidget(aboutButton);
    aboutButton->setExecuteFunction(
        [this] ()
        {
            setActiveScene(aboutSettings);
        }
    );
    aboutSettings->setPreviousScene(settings);
}
