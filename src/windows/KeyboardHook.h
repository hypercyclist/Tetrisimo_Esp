#ifndef KEYBOARDHOOK
#define KEYBOARDHOOK

class Config;
class Display;

class GLFWwindow;

#include <memory>
#include <vector>

enum class KeyboardKeys {
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_OK,
    KEY_BACK,
    NO_KEY
};

// This class help to determine which physical button was pressed. Firstly
// we add all buttons, that it must controll, then check is buttons pressed.
class KeyboardHook
{
    private:
        std::shared_ptr<Config> config;
        GLFWwindow* window;
    public:
        KeyboardHook(std::shared_ptr<Config> _config, std::shared_ptr<Display> _display);
        ~KeyboardHook();
        KeyboardKeys getPressedButton();
};

#endif
