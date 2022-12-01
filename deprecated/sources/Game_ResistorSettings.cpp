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
#include "TableView.h"
// #include "TextView.h"
// #include "DefineTime.h"
#include "VerticalLayout.h"

// #include "Log.h"

// #include "Color.h"

void Game::initializeResistorSettings()
{
    resistorsSettings = std::make_shared<Scene>( shared_from_this() );
    configureBasicMenuScene(resistorsSettings, "Резисторы", 2);
    std::shared_ptr<VerticalLayout> resistorsSettingsLayout = 
        std::static_pointer_cast<VerticalLayout>( resistorsSettings->getCentralWidget() );

    std::shared_ptr<TableView> resistorTable = std::make_shared<TableView>
        ("Сопротивления");
    resistorTable->addText("1.Вверх      100R");
    resistorTable->addText("2.Вниз       150R");
    resistorTable->addText("3.Влево        3К");
    resistorTable->addText("4.Вправо     5.5К");
    resistorTable->addText("5.ОК          48К");
    resistorTable->addText("6.Назад       57К");
    resistorTable->addText("7.Подтягивающий  ");
    resistorTable->addText("              10К");
    resistorsSettingsLayout->addWidget(resistorTable);
}