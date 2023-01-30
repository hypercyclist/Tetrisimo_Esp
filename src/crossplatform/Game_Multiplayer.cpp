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
// #include "TextView.h"
#include "Layout.h"

// #include "Color.h"

void Game::initializeMultiplayer()
{
    multiplayer = std::make_shared<Scene>( shared_from_this(), background, "Сеть", 2);
    std::shared_ptr<Layout> multiplayerLayout = 
        std::static_pointer_cast<Layout>( multiplayer->getCentralWidget() );

    std::shared_ptr<Button> clientButton = std::make_shared<Button>("Я клиент");
    multiplayerLayout->addWidget(clientButton);

    std::shared_ptr<Button> hostButton = std::make_shared<Button>("Я сервер");
    multiplayerLayout->addWidget(hostButton);
}