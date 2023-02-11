#include "KeyboardHook.h"

#include "Config.h"
#include "Display.h"
#include "Log.h"
#include "PlatformTime.h"

#include "GLFW/glfw3.h"

KeyboardKeys KeyboardHook::lastInput = KeyboardKeys::NO_KEY;

void getPressedButtonCallback(GLFWwindow* _window, int _key, 
    int _scancode, int _action, int _mods);

KeyboardHook::KeyboardHook(std::shared_ptr<Config> _config, std::shared_ptr<Display> _display) : 
    INPUT_DELAY(150),
    config(_config),
    window(_display->getWindow()),
    lastInputTimeMs(0)
{
    glfwSetKeyCallback (window, getPressedButtonCallback);
}

KeyboardHook::~KeyboardHook() { }

void getPressedButtonCallback(GLFWwindow* _window, int _key, 
    int _scancode, int _action, int _mods)
{
    bool keyUpState = _key == GLFW_KEY_UP && _action == GLFW_PRESS ? true : false;
    bool keyDownState = _key == GLFW_KEY_DOWN && _action == GLFW_PRESS ? true : false;
    bool keyLeftState = _key == GLFW_KEY_LEFT && _action == GLFW_PRESS ? true : false;
    bool keyRightState = _key == GLFW_KEY_RIGHT && _action == GLFW_PRESS ? true : false;
    bool keyOkState = _key == GLFW_KEY_ENTER && _action == GLFW_PRESS ? true : false;
    bool keyBackState = _key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS ? true : false;

    if (keyUpState) KeyboardHook::setLastInput(KeyboardKeys::KEY_UP);
    else if (keyDownState) KeyboardHook::setLastInput(KeyboardKeys::KEY_DOWN);
    else if (keyLeftState) KeyboardHook::setLastInput(KeyboardKeys::KEY_LEFT);
    else if (keyRightState) KeyboardHook::setLastInput(KeyboardKeys::KEY_RIGHT);
    else if (keyOkState) KeyboardHook::setLastInput(KeyboardKeys::KEY_OK);
    else if (keyBackState) KeyboardHook::setLastInput(KeyboardKeys::KEY_BACK);
}

KeyboardKeys KeyboardHook::getPressedButton()
{
    time_t time = PlatformTime::getTimeMs();
    if ((time - lastInputTimeMs) < INPUT_DELAY) return KeyboardKeys::NO_KEY;
    KeyboardKeys tempLastInput = lastInput;
    lastInput = KeyboardKeys::NO_KEY;
    lastInputTimeMs = time;
    return tempLastInput;
}

void KeyboardHook::setLastInput(KeyboardKeys _key) { KeyboardHook::lastInput = _key; }
