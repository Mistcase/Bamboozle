#include "Bubble/bubblepch.h"
#include "WindowsInput.h"

#include "Bubble/Application.h"
#include <GLFW/glfw3.h>

namespace bubble
{
	Input* Input::m_instance = new WindowsInput();

	bool WindowsInput::isKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetInstance().getWindow().getNativeWindow());
		const auto state = glfwGetKey(window, keycode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::GetInstance().getWindow().getNativeWindow());
		const auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::getMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::GetInstance().getWindow().getNativeWindow());
		double xPos, yPos;

		glfwGetCursorPos(window, &xPos, &yPos);

		return { static_cast<float>(xPos), static_cast<float>(yPos) };
	}

	float WindowsInput::getMouseXImpl()
	{
		auto [x, y] = getMousePositionImpl();
		return x;
	}

	float WindowsInput::getMouseYImpl()
	{
		auto [x, y] = getMousePositionImpl();
		return y;
	}

} // namespace bubble
