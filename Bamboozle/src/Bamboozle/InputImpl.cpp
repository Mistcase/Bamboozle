#include "InputImpl.h"

#include "Bamboozle/Application.h"
#include "Bamboozle/bbzl.h"
#include <GLFW/glfw3.h>

namespace bbzl
{
    Input* Input::m_instance = new InputImpl();

    bool InputImpl::isKeyPressedImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::GetInstance().getWindow().getNativeWindow());
        const auto state = glfwGetKey(window, keycode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool InputImpl::IsMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow*>(Application::GetInstance().getWindow().getNativeWindow());
        const auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> InputImpl::getMousePositionImpl()
    {
        auto window = static_cast<GLFWwindow*>(Application::GetInstance().getWindow().getNativeWindow());
        double xPos, yPos;

        glfwGetCursorPos(window, &xPos, &yPos);

        return { static_cast<float>(xPos), static_cast<float>(yPos) };
    }

    float InputImpl::getMouseXImpl()
    {
        auto [x, y] = getMousePositionImpl();
        return x;
    }

    float InputImpl::getMouseYImpl()
    {
        auto [x, y] = getMousePositionImpl();
        return y;
    }

} // namespace bbzl
