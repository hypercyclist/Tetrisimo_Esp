#ifndef GAME_H
#define GAME_H

class Background;
class Config;
class Display;
class KeyboardHook;
class Size;
class Scene;
enum class KeyboardKeys;

#include <memory>
#include <time.h>

// Game class initialize and connects all parts together.
class Game : public std::enable_shared_from_this<Game>
{
    private:
        bool gameRunning;
        std::shared_ptr<Config> config;
        std::shared_ptr<KeyboardHook> keyboardHook;
        std::shared_ptr<Display> display;
        // Always point to current scene.
        std::shared_ptr<Scene> activeScene;

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
        std::shared_ptr<Scene> highScore;
        std::shared_ptr<Scene> widgetViewer;

        void initialize();
        void initializeConfig();
        void initializeDisplay();
        void initializeKeyboardHook();
        void initializeBackground();
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
        void initializeWidgetViewer();
        void initializeHighScore();
        void run();
        void processKeyboard();

    public:
        Game();
        ~Game();
        void start();
        void stop();
        std::shared_ptr<Display> getDisplay();
        std::shared_ptr<Scene> getActiveScene();
        void setActiveScene(std::shared_ptr<Scene> _activeScene);
};

#endif
