#include "KeyboardHook.h"

#include "Config.h"
#include "Display.h"
#include "Log.h"

#include "GLFW/glfw3.h"


KeyboardHook::KeyboardHook(std::shared_ptr<Config> _config, std::shared_ptr<Display> _display)
    : config(_config),
    window(_display->getWindow())
{
}

KeyboardHook::~KeyboardHook()
{
}

KeyboardKeys KeyboardHook::getPressedButton()
{
    int keyUpState = glfwGetKey(window, GLFW_KEY_UP);
    int keyDownState = glfwGetKey(window, GLFW_KEY_DOWN);
    int keyLeftState = glfwGetKey(window, GLFW_KEY_LEFT);
    int keyRightState = glfwGetKey(window, GLFW_KEY_RIGHT);
    int keyOkState = glfwGetKey(window, GLFW_KEY_ENTER);
    int keyBackState = glfwGetKey(window, GLFW_KEY_ESCAPE);

    if (keyUpState == GLFW_PRESS) return KeyboardKeys::KEY_UP;
    if (keyDownState == GLFW_PRESS) return KeyboardKeys::KEY_DOWN;
    if (keyLeftState == GLFW_PRESS) return KeyboardKeys::KEY_LEFT;
    if (keyRightState == GLFW_PRESS) return KeyboardKeys::KEY_RIGHT;
    if (keyOkState == GLFW_PRESS) return KeyboardKeys::KEY_OK;
    if (keyBackState == GLFW_PRESS) return KeyboardKeys::KEY_BACK;

    return KeyboardKeys::NO_KEY;
}
