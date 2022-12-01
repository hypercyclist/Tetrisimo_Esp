#include "Game.h"

// #include "Background.h"
#include "Button.h"
// #include "CheckBox.h"
// #include "Config.h"
#include "Display.h"
// #include "KeyboardHook.h"
// #include "Label.h"
#include "LineEdit.h"
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
#include "VerticalLayout.h"

// #include "Log.h"

// #include "Color.h"

void Game::initializeAdvancedSettings()
{
    advansedSettings = std::make_shared<Scene>( shared_from_this() );
    configureBasicMenuScene(advansedSettings, "Другие", 2);
    std::shared_ptr<VerticalLayout> advansedSettingsLayout = 
        std::static_pointer_cast<VerticalLayout>( advansedSettings->getCentralWidget() );

    std::shared_ptr<LineEdit> globalIpLineEdit = std::make_shared<LineEdit>
        ("Адрес гл. сервера", "193.9.61.92");
    advansedSettingsLayout->addWidget(globalIpLineEdit);
    std::shared_ptr<LineEdit> globalPortLineEdit = std::make_shared<LineEdit>
        ("Порт гл. сервера", "6452");
    advansedSettingsLayout->addWidget(globalPortLineEdit);
    std::shared_ptr<Button> resistorsButton = std::make_shared<Button>("Резисторы");
    advansedSettingsLayout->addWidget(resistorsButton);
    resistorsButton->setExecuteFunction(
        [this] ()
        {
            display->setActiveScene(resistorsSettings);
        }
    );
    resistorsSettings->setPreviousScene(advansedSettings);
    std::shared_ptr<Button> hardResetButton = std::make_shared<Button>("Сброс");
    advansedSettingsLayout->addWidget(hardResetButton);
}
