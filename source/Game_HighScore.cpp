#include "Game.h"

// #include "Background.h"
#include "Button.h"
// #include "CheckBox.h"
// #include "Config.h"
#include "DefineDisplay.h"
// #include "KeyboardHook.h"
// #include "Label.h"
// #include "LineEdit.h"
#include "DefinePainter.h"
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

// #include "DefineLog.h"

// #include "Color.h"

void Game::initializeHighScore()
{
    highScore = std::make_shared<Scene>( shared_from_this() );
    configureBasicMenuScene(highScore, "Рекорды", 2);
    std::shared_ptr<VerticalLayout> highScoreLayout = 
        std::static_pointer_cast<VerticalLayout>( highScore->getCentralWidget() );

    std::shared_ptr<TableView> personalBest = std::make_shared<TableView>
        ("Мои рекорды");
    personalBest->addText("1...............0");
    personalBest->addText("2...............0");
    personalBest->addText("3...............0");
    personalBest->addText("4...............0");
    personalBest->addText("5...............0");
    personalBest->addText("6...............0");
    personalBest->addText("7...............0");
    personalBest->addText("8...............0");
    personalBest->addText("9...............0");
    personalBest->addText("10..............0");
    personalBest->minimize();
    personalBest->focus();
    personalBest->setExecuteFunction(
        [this, personalBest] ()
        {
            widgetViewer->setPreviousScene(highScore);
            std::static_pointer_cast<VerticalLayout>(widgetViewer->getCentralWidget())->addWidget(personalBest);
            display->setActiveScene(widgetViewer);
        }
    );
    highScoreLayout->addWidget(personalBest);

    std::shared_ptr<TableView> networkBest = std::make_shared<TableView>
        ("Интернет рекорды");
    networkBest->addText("1...............0");
    networkBest->addText("2...............0");
    networkBest->addText("3...............0");
    networkBest->addText("4...............0");
    networkBest->addText("5...............0");
    networkBest->addText("6...............0");
    networkBest->addText("7...............0");
    networkBest->addText("8...............0");
    networkBest->addText("9...............0");
    networkBest->addText("10..............0");
    networkBest->minimize();
    highScoreLayout->addWidget(networkBest);
}
