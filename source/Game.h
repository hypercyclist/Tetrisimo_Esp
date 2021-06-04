#ifndef GAME_H
#define GAME_H

class Size;
class Config;
class KeyboardHook;
class Background;
class Scene;
class PhysButton;
class Display;
#include <memory>
#include <time.h>

class Game : public std::enable_shared_from_this<Game>
{
    private:
        std::shared_ptr<Config> config;
        std::shared_ptr<PhysButton> buttonUp;
        std::shared_ptr<PhysButton> buttonDown;
        std::shared_ptr<PhysButton> buttonLeft;
        std::shared_ptr<PhysButton> buttonRight;
        std::shared_ptr<PhysButton> buttonOk;
        std::shared_ptr<PhysButton> buttonBack;
        std::shared_ptr<KeyboardHook> keyboardHook;

        std::shared_ptr<Background> background;
        std::shared_ptr<Scene> mainMenu;
        std::shared_ptr<Scene> singleGame;
        std::shared_ptr<Scene> multiplayer;
        std::shared_ptr<Scene> serverBrowser;
        std::shared_ptr<Scene> createServer;
        std::shared_ptr<Scene> cooperativeGame;
        std::shared_ptr<Scene> versusGame;
        std::shared_ptr<Scene> settings;
        std::shared_ptr<Scene> gameSettings;
        std::shared_ptr<Scene> networkSettings;
        std::shared_ptr<Scene> advansedSettings;
        std::shared_ptr<Scene> resistorsSettings;
        std::shared_ptr<Scene> colorsSettings;
        std::shared_ptr<Scene> customColorsSettings;
        std::shared_ptr<Scene> customFigureSettings;
        std::shared_ptr<Scene> aboutSettings;
        std::shared_ptr<Scene> keyboard;
        std::shared_ptr<Scene> highScore;
        std::shared_ptr<Display> display;

        time_t inputTimeStartMs;
        time_t getTimeMs();

    public:
        Game();
        ~Game();
        void start();
        void initialize();
        void run();
        void processPressedButton(std::shared_ptr<PhysButton> _pressedButton);
        void initializeConfig();
        void initializeButtons();
        void initializeDisplay();
        void initializeBackground();
        void initializeBasicScene(std::shared_ptr<Scene> _scene, 
            std::string _headerText, int _headerTextSize);
        void initializeMainMenu();
        void initializeSingleGame();
        void initializeMultiplayer();
        void initializeServerBrowser();
        void initializeCreateServer();
        void initializeCooperativeGame();
        void initializeVersusGame();
        void initializeSettings();
        void initializeGameSettings();
        void initializeNetworkSettings();
        void initializeAdvancedSettings();
        void initializeResistorSettings();
        void initializeColorsSettings();
        void initializeCustomColorsSettings();
        void initializeCustomFigureSettings();
        void initializeAboutSettings();
        std::shared_ptr<Display> getDisplay();

        void beep();
};

#endif
