#ifndef SCENE_H
#define SCENE_H

#include "Widget.h"
class Background;

#include <vector>
#include <memory>
#include <functional>

class Scene : public Widget
{
    private:
        std::shared_ptr<Background> background;
        std::shared_ptr<Widget> widget;
        std::shared_ptr<Scene> previousScene;
        int framesPerSeconds;

        std::function<void()> pressedButtonUpFunctionPointer;
        std::function<void()> pressedButtonDownFunctionPointer;
        std::function<void()> pressedButtonRightFunctionPointer;
        std::function<void()> pressedButtonLeftFunctionPointer;
        std::function<void()> pressedButtonOkFunctionPointer;
        std::function<void()> pressedButtonBackFunctionPointer;
    
    public:
        Scene(std::shared_ptr<Widget> _parent = nullptr);
        ~Scene();

        void render();
        // void redraw();
        // void processChild(std::shared_ptr<Widget> _child);
        
        std::shared_ptr<Scene> getPreviousScene();
        void setPreviousScene(std::shared_ptr<Scene> _previousScene);
        void setBackgroundWidget(std::shared_ptr<Background> _background);
        void setCentralWidget(std::shared_ptr<Widget> _widget);
        
        int getFrameTime();
        void setFrameTime(int _framesPerSeconds);

        void initializeStandartFunctions();
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
