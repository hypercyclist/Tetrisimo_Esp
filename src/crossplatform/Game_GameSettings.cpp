#include "Game.h"

// #include "Background.h"
#include "Button.h"
#include "CheckBox.h"
#include "Config.h"
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

void Game::initializeGameSettings()
{
    gameSettings = std::make_shared<Scene>( shared_from_this(), background, "Настройки", 2);
    std::shared_ptr<Layout> gameSettingsLayout = 
        std::static_pointer_cast<Layout>( gameSettings->getCentralWidget() );

    std::shared_ptr<CheckBox> useNetButton = std::make_shared<CheckBox>("Сетка", config->getUseNetState());
    gameSettingsLayout->addWidget(useNetButton);
    useNetButton->setExecuteFunction(
        [this, useNetButton] ()
        {
            useNetButton->setState( !useNetButton->getState() );
        }
    );

    std::shared_ptr<CheckBox> useGhostButton = std::make_shared<CheckBox>("Тень", config->getUseGhostState());
    gameSettingsLayout->addWidget(useGhostButton);
    useGhostButton->setExecuteFunction(
        [this, useGhostButton] ()
        {
            useGhostButton->setState( !useGhostButton->getState() );
        }
    );

    std::shared_ptr<CheckBox> useVibrationButton = std::make_shared<CheckBox>("Вибро", config->getUseVibrationState());
    gameSettingsLayout->addWidget(useVibrationButton);
    useVibrationButton->setExecuteFunction(
        [this, useVibrationButton] ()
        {
            useVibrationButton->setState( !useVibrationButton->getState() );
        }
    );

    gameSettings->setOnHideFunction(
        [this, useNetButton, useGhostButton, useVibrationButton] () 
        {
            gameSettings->unfocus();
            config->setUseNetState(useNetButton->getState());
            config->setUseGhostState(useGhostButton->getState());
            config->setUseVibrationState(useVibrationButton->getState());
            config->writeConfig();
        }
    );
}
