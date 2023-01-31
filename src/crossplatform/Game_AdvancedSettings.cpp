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
#include "Layout.h"

// #include "Log.h"

// #include "Color.h"

void Game::initializeAdvancedSettings()
{
    advansedSettings = std::make_shared<Scene>( shared_from_this());
    advansedSettings->configureBasicMenuScene(background, "Другие", 2);

    std::shared_ptr<LineEdit> globalIpLineEdit = std::make_shared<LineEdit>
        ("Адрес гл. сервера", "193.9.61.92");
    advansedSettings->getLayout()->addWidget(globalIpLineEdit);
    globalIpLineEdit->setExecuteFunction(
        [this, globalIpLineEdit] ()
        {
            widgetViewer->setPreviousScene(advansedSettings);
            widgetViewer->getLayout()->addWidget(globalIpLineEdit);
            setActiveScene(widgetViewer);
        }
    );
    std::shared_ptr<LineEdit> globalPortLineEdit = std::make_shared<LineEdit>
        ("Порт гл. сервера", "6452");
    advansedSettings->getLayout()->addWidget(globalPortLineEdit);
    globalPortLineEdit->setExecuteFunction(
        [this, globalPortLineEdit] ()
        {
            widgetViewer->setPreviousScene(advansedSettings);
            widgetViewer->getLayout()->addWidget(globalPortLineEdit);
            setActiveScene(widgetViewer);
        }
    );
    // std::shared_ptr<Button> resistorsButton = std::make_shared<Button>("Резисторы");
    // advansedSettingsLayout->addWidget(resistorsButton);
    // resistorsButton->setExecuteFunction(
    //     [this] ()
    //     {
    //         setActiveScene(resistorsSettings);
    //     }
    // );
    // resistorsSettings->setPreviousScene(advansedSettings);
    std::shared_ptr<Button> hardResetButton = std::make_shared<Button>("Сброс");
    advansedSettings->getLayout()->addWidget(hardResetButton);
}
