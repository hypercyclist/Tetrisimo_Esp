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
#include "PaletteView.h"
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

void Game::initializeColorsSettings()
{
    colorsSettings = std::make_shared<Scene>( shared_from_this(), background, "Палитра", 2);
    std::shared_ptr<VerticalLayout> colorsSettingsLayout = 
        std::static_pointer_cast<VerticalLayout>( colorsSettings->getCentralWidget() );

    std::shared_ptr<PaletteView> paletteView = std::make_shared<PaletteView>();
    colorsSettingsLayout->addWidget(paletteView);
    std::shared_ptr<TableView> colorThemesTable = std::make_shared<TableView>("Цветовые темы");
    colorsSettingsLayout->addWidget(colorThemesTable);
    colorThemesTable->addText("1.Пещерные огни");
    colorThemesTable->addText("2.Кровавая тряска");
    colorThemesTable->addText("3.Своя тема");

}
