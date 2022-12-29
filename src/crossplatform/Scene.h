#ifndef SCENE_H
#define SCENE_H

class Background;
class Game;

#include "Widget.h"

#include <functional>
#include <memory>
#include <vector>

// This class describe ingame widget scene.
class Scene : public Widget
{
    private:
        // Every scene know single game object. Game is scene parent.
        std::shared_ptr<Game> game;
        // std::shared_ptr<Background> background;
        // std::shared_ptr<Widget> widget;
        // If scene was changed from parent to it, then we should be able to come
        // back to parent scene.
        std::shared_ptr<Scene> previousScene;
        // If our scene is static, then we can decrease game framerate. Or increase.
        int framesPerSeconds;

        void configureBasicMenuScene(std::shared_ptr<Background> _background, 
            std::string _headerText, int _headerTextSize);
        // This is a pointers to functions, that was set from lambda.
        std::function<void()> onShowFunctionPointer;
        std::function<void()> onHideFunctionPointer;

        std::function<void()> pressedButtonUpFunctionPointer;
        std::function<void()> pressedButtonDownFunctionPointer;
        std::function<void()> pressedButtonRightFunctionPointer;
        std::function<void()> pressedButtonLeftFunctionPointer;
        std::function<void()> pressedButtonOkFunctionPointer;
        std::function<void()> pressedButtonBackFunctionPointer;
    
    public:
        Scene(std::shared_ptr<Game> _game);
        Scene(std::shared_ptr<Game> _game, 
            std::shared_ptr<Background> _background, std::string _headerText, 
            int _headerTextSize);
        ~Scene();

        // void render();
        // void redraw();
        // void processChild(std::shared_ptr<Widget> _child);
        
        std::shared_ptr<Scene> getPreviousScene();
        void setPreviousScene(std::shared_ptr<Scene> _previousScene);
        void setBackgroundWidget(std::shared_ptr<Background> _background);
        std::shared_ptr<Widget> getBackground();
        void setCentralWidget(std::shared_ptr<Widget> _widget);
        std::shared_ptr<Widget> getCentralWidget();
        
        int getFrameTime();
        void setFrameTime(int _framesPerSeconds);

        void initializeStandartFunctions();
        void onShow();
        void setOnShowFunction(std::function<void()> _function);
        void onHide();
        void setOnHideFunction(std::function<void()> _function);

        void pressedButtonUp();
        void setPressedButtonUpFunction(std::function<void()> _function);
        void pressedButtonDown();
        void setPressedButtonDownFunction(std::function<void()> _function);
        void pressedButtonLeft();
        void setPressedButtonLeftFunction(std::function<void()> _function);
        void pressedButtonRight();
        void setPressedButtonRightFunction(std::function<void()> _function);
        void pressedButtonOk();
        void setPressedButtonOkFunction(std::function<void()> _function);
        void pressedButtonBack();
        void setPressedButtonBackFunction(std::function<void()> _function);
};

#endif

// virtual void logic();
// virtual void input(int);
// virtual void setForceUpdate();

// static void setActiveScene(Scene*);
// static Scene* getActiveScene();
// static void setKeyBoardScene(SC_KeyBoard*);
// static void toKeyBoardFrom(Component*, Scene*);
