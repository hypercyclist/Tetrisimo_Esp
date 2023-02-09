#include "VirtualKeyboard.h"
#include "Layout.h"
#include "Button.h"

VirtualKeyboard::VirtualKeyboard()
{
    isLetterUpperCase = false;
    isNumsUpperCase = false;
    editableWidgetLinesCount = 1;
    textLayouts.resize(4);
    textLayouts.at(ENGLISH_LOWER).resize(4);
    textLayouts.at(ENGLISH_LOWER)[0] = {"q", "w", "e", "r", "t", "y", "u", "i", "o", "p"};
    textLayouts.at(ENGLISH_LOWER)[1] = {"a", "s", "d", "f", "g", "h", "j", "k", "l"};
    textLayouts.at(ENGLISH_LOWER)[2] = {"Aa", "z", "x", "c", "v", "b", "n", "m", "<-"};
    textLayouts.at(ENGLISH_LOWER)[3] = {"#1", ",", "Ln", " ", ".", "Ok"};
    
    textLayouts.at(ENGLISH_UPPER).resize(4);
    textLayouts.at(ENGLISH_UPPER)[0] = {"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"};
    textLayouts.at(ENGLISH_UPPER)[1] = {"A", "S", "D", "F", "G", "H", "J", "K", "L"};
    textLayouts.at(ENGLISH_UPPER)[2] = {"Aa", "Z", "X", "C", "V", "B", "N", "M", "<-"};
    textLayouts.at(ENGLISH_UPPER)[3] = {"#1", ",", "Ln", " ", ".", "Ok"};
    
    textLayouts.at(NUMERIC_LOWER).resize(4);
    textLayouts.at(NUMERIC_LOWER)[0] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
    textLayouts.at(NUMERIC_LOWER)[1] = {"@", "#", "_", "&", "-", "+", "(", ")", "/"};
    textLayouts.at(NUMERIC_LOWER)[2] = {"<>", "*", "\"", "'", ":", ";", "!", "?", "<-"};
    textLayouts.at(NUMERIC_LOWER)[3] = {"Ab", ",", "Ln", " ", ".", "Ok"};

    textLayouts.at(NUMERIC_UPPER).resize(4);
    textLayouts.at(NUMERIC_UPPER)[0] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"};
    textLayouts.at(NUMERIC_UPPER)[1] = {"~", "`", "|", "/", "*", "^", "{", "}"};
    textLayouts.at(NUMERIC_UPPER)[2] = {"<>", "[", "]", "%", "<", ">", "=", "<-"};
    textLayouts.at(NUMERIC_UPPER)[3] = {"Ab", ",", "Ln", " ", ".", "Ok"};
}

void VirtualKeyboard::createGraphics()
{
    layouts.resize(4);
    for(int i = 0; i < textLayouts.size(); i++)
    {
        layouts[i] = std::make_shared<Layout>();
        for(int j = 0; j < textLayouts[i].size(); j++)
        {
            layouts[i]->addWidget(std::make_shared<Layout>());

            int totalRowSize = 0;
            for(int k = 0; k < textLayouts[i][j].size(); k++)
            {
                if (textLayouts[i][j][k] == " ")
                {
                    totalRowSize += WIDTH_L;
                }
                else if (textLayouts[i][j][k].length() > 1)
                {
                    totalRowSize += WIDTH_M;
                }
                else
                {
                    totalRowSize += WIDTH_S;
                }
            }
            int widgetWidth;
            for(int k = 0; k < textLayouts[i][j].size(); k++)
            {
                if (textLayouts[i][j][k] == " ")
                {
                    widgetWidth = WIDTH_L;
                }
                else if (textLayouts[i][j][k].length() > 1)
                {
                    widgetWidth = WIDTH_M;
                }
                else
                {
                    widgetWidth = WIDTH_S;
                }
                std::shared_ptr<Button> button = 
                    std::make_shared<Button>(textLayouts[i][j][k]);
                std::static_pointer_cast<Layout>(
                    layouts[i]->getWidget(j))->setLayoutType(LayoutType::HORIZONTAL);
                std::static_pointer_cast<Layout>(
                    layouts[i]->getWidget(j))->addWidget(button);
                button->setTextSize(1);
                // setFunction(button);
            }
        }
        getLayout()->addWidget(layouts[i]);
        // layouts[i]->setFocus(1, 4);
    }

    currentLayout = layouts[0];
    currentLayout->countLayout();
}

VirtualKeyboard::~VirtualKeyboard()
{
    // delete gridMenu;
}

void VirtualKeyboard::render()
{
    // editableWidgetLinesCount = ((LineEdit*)editableWidget)->getLinesCount();
    // editableWidget->render();
    currentLayout->render();
}

// void VirtualKeyboard::drawKeyboard()
// {
//     int keyBoardY = config->screenHeight - currentLayout->getRows() * 13 - 3;
//     tft->fillRect(0, keyBoardY, config->screenWidth, config->screenHeight - keyBoardY, tft->calculateColor(8, 8, 8));
//     tft->drawRect(0, keyBoardY, config->screenWidth, config->screenHeight - keyBoardY, tft->calculateColor(0, 0, 0));
//     currentLayout->setForceUpdate();
// }

// void VirtualKeyboard::drawHeader()
// {
//     tft->setRotation(0);
//     tft->setTextColor(config->styleRedColor);
//     tft->setTextSize(2);
//     tft->drawText("Keyboard", 16, 8);
//     tft->setPenColor(config->styleRedColor);
//     tft->drawLine(9,26,117,26);
//     tft->drawLine(9,27,117,27);
// }

// void VirtualKeyboard::drawMenu()
// {
//     currentLayout->draw();
// }

// void VirtualKeyboard::logic()
// {

// }

// void VirtualKeyboard::input(int _input)
// {
//     InputQualifier::ButtonType buttonType = inputQualifier->getButtonType(_input);
//     // Component* component = verticalMenu->components[verticalMenu->currentComponentIndex];
//     if(buttonType == InputQualifier::ButtonType::BUTTON_OK)
//     {
//         currentLayout->getCurrentComponent()->execute(this);
//         // component->execute(this);
//         // if(buttonText == "Custom")
//         // {
//         //     Scene::setActiveScene(custom);
//         //     custom->setForceUpdate();
//         // }
//     }
//     if(buttonType == InputQualifier::ButtonType::BUTTON_BACK)
//     {
//         editableWidget->setX(editableWidgetOldX);
//         editableWidget->setY(editableWidgetOldY);
//         ((LineEdit*)editableWidget)->setShowFull(false);
//         Scene::setActiveScene(parentScene);
//         parentScene->setForceUpdate();
//     }
//     if(buttonType == InputQualifier::ButtonType::BUTTON_RIGHT)
//     {
//         currentLayout->switchToNextColumn();
//     }
//     if(buttonType == InputQualifier::ButtonType::BUTTON_LEFT)
//     {
//         currentLayout->switchToPreviousColumn();
//     }
//     if(buttonType == InputQualifier::ButtonType::BUTTON_DOWN)
//     {
//         currentLayout->switchToNextRow();
//     }
//     if(buttonType == InputQualifier::ButtonType::BUTTON_UP)
//     {
//         currentLayout->switchToPreviousRow();
//     }
// }

// void VirtualKeyboard::setEditableWidget(Component* _editableWidget)
// {
//     editableWidget = _editableWidget;
// }

// void VirtualKeyboard::setForceUpdate()
// {
//     isSceneRendered = false;
// }

// void VirtualKeyboard::setLayout(TextLayout _layout)
// {
//     int row = currentLayout->currentRowIndex;
//     int column = currentLayout->currentColumnIndex;
//     currentLayout = layouts[_layout];
//     currentLayout->setFocus(row, column);
//     drawKeyboard();
// }

// void VirtualKeyboard::setFunction(Button* _button)
// {
//     String buttonText = _button->getText(); 
//     if(buttonText == "Aa")
//     {
//         _button->setExecuteFunction (
//             [](Scene* _scene, Component* _component)
//             {
//                 VirtualKeyboard* scene = ((VirtualKeyboard*)_scene);
//                 if(scene->isLetterUpperCase)
//                 {
//                     scene->setLayout(ENGLISH_LOWER);
//                 }
//                 else
//                 {
//                    scene->setLayout(ENGLISH_UPPER);
//                 }
//                 scene->isLetterUpperCase = !scene->isLetterUpperCase;
//             }
//         );
//     }
//     else if(buttonText == "<>")
//     {
//         _button->setExecuteFunction (
//             [](Scene* _scene, Component* _component)
//             {
//                 VirtualKeyboard* scene = ((VirtualKeyboard*)_scene);
//                 if(scene->isNumsUpperCase)
//                 {
//                     scene->setLayout(NUMERIC_LOWER);
//                 }
//                 else
//                 {
//                     scene->setLayout(NUMERIC_UPPER);
//                 }
//                 scene->isNumsUpperCase = !scene->isNumsUpperCase;
//             }
//         );
//     }
//     else if(buttonText == "<-")
//     {
//         _button->setExecuteFunction (
//             [](Scene* _scene, Component* _component)
//             {
//                 LineEdit* editableWidget = ((LineEdit*)((VirtualKeyboard*)_scene)->editableWidget);
//                 editableWidget->setText(editableWidget->getText().substring(0, editableWidget->getText().length() - 1));
//                 editableWidget->setForceUpdate();
//             }
//         );
//     }
//     else if(buttonText == "#1")
//     {
//         _button->setExecuteFunction (
//             [](Scene* _scene, Component* _component)
//             {
//                 VirtualKeyboard* scene = ((VirtualKeyboard*)_scene);
//                 scene->setLayout(NUMERIC_LOWER);
//             }
//         );
//     }
//     else if(buttonText == "Ab")
//     {
//         _button->setExecuteFunction (
//             [](Scene* _scene, Component* _component)
//             {
//                 VirtualKeyboard* scene = ((VirtualKeyboard*)_scene);
//                 scene->setLayout(ENGLISH_LOWER);
//             }
//         );
//     }
//     else if(buttonText == "Ln")
//     {
//         _button->setExecuteFunction (
//             [](Scene* _scene, Component* _component)
//             {

//             }
//         );
//     }
//     else if(buttonText == "Ok")
//     {
//         _button->setExecuteFunction (
//             [](Scene* _scene, Component* _component)
//             {
//                 Scene::setActiveScene(_scene->getParentScene());
//                 _scene->getParentScene()->setForceUpdate();
//             }
//         );
//     }
//     else
//     {
//         _button->setExecuteFunction (
//             [](Scene* _scene, Component* _component)
//             {
//                 LineEdit* editableWidget = ((LineEdit*)((VirtualKeyboard*)_scene)->editableWidget);
//                 editableWidget->setText(editableWidget->getText() +
//                     ((Button*)_component)->getText()
//                 );
//                 editableWidget->setForceUpdate();
//             }
//         );
//     }
// }