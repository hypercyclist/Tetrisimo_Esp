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
#include "Size.h"
#include "Scene.h"
// #include "TableView.h"
// #include "TextView.h"
// #include "DefineTime.h"
#include "VerticalLayout.h"

// #include "Log.h"

// #include "Color.h"

void Game::initializeWidgetViewer()
{
    widgetViewer = std::make_shared<Scene>( shared_from_this() );
    widgetViewer->setSize( display->getSize() );
    widgetViewer->setBackgroundWidget(background);

    std::shared_ptr<VerticalLayout> widgetViewerLayout = std::make_shared<VerticalLayout>();
    widgetViewer->setCentralWidget(widgetViewerLayout);
    widgetViewer->setOnShowFunction(
        [this, widgetViewerLayout] ()
        {
            widgetViewerLayout->getWidget(0)->maximize();
        }
    );
    widgetViewer->setOnHideFunction(
        [this, widgetViewerLayout] ()
        {
            widgetViewerLayout->getWidget(0)->minimize();
            widgetViewerLayout->removeChildren(widgetViewerLayout->getWidget(0));
        }
    );
}
