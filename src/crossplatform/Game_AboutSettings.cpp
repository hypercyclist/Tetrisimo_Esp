#include "Game.h"

// #include "Background.h"
#include "Button.h"
// #include "CheckBox.h"
// #include "Config.h"
// #include "KeyboardHook.h"
// #include "Label.h"
// #include "LineEdit.h"
// #include "PaletteView.h"
// #include "PhysButton.h"
// #include "Point.h"
// #include "Resistor.h"
// #include "ResourceTheme.h"
// #include "Size.h"
#include "Scene.h"
// #include "TableView.h"
#include "TextView.h"
#include "Layout.h"

// #include "Color.h"

void Game::initializeAboutSettings()
{
    aboutSettings = std::make_shared<Scene>( shared_from_this(), background, "О проекте", 2);
    std::shared_ptr<Layout> aboutSettingsLayout = 
        std::static_pointer_cast<Layout>( aboutSettings->getCentralWidget() );

    std::shared_ptr<TextView> thanksTable = std::make_shared<TextView>
        ("Спасибо!", "Никите, Льву, Анастасии, Дмитрию, Игорю, Александру, Александре");
    aboutSettingsLayout->addWidget(thanksTable);
    std::shared_ptr<TextView> contactsTable = std::make_shared<TextView>
        ("Контакты", "warstar441@gmail.com");
    aboutSettingsLayout->addWidget(contactsTable);
}