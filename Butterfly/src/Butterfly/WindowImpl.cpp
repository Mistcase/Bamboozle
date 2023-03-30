#include "WindowImpl.h"

#include "Butterfly/Events/ApplicationEvent.h"
#include "Butterfly/Events/KeyEvent.h"
#include "Butterfly/Events/MouseEvent.h"
#include "Butterfly/Log.h"
#include "Butterfly/butterflypch.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace
{
    void GLFWErrorCallback(int error, const char* desc)
    {
        BUTTERFLY_CORE_ERROR("GLFW Error ({0}): {1}", error, desc);
    }

} // namespace

namespace butterfly
{
    static bool GLFWInitialized = false;

    Window* Window::Create(const WindowProps& props)
    {
        return new WindowImpl(props);
    }

    WindowImpl::WindowImpl(const WindowProps& props)
    {
        init(props);
    }

    WindowImpl::~WindowImpl()
    {
        shutdown();
    }

    void WindowImpl::init(const WindowProps& props)
    {
        m_data.title = props.title;
        m_data.width = props.width;
        m_data.height = props.height;

        BUTTERFLY_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

        if (!GLFWInitialized)
        {
            // TODO: glfwTerminate on system shutdown
            int success = glfwInit();
            BUTTERFLY_CORE_ASSERT(success, "Could not intialize GLFW!");

            glfwSetErrorCallback(GLFWErrorCallback);
            GLFWInitialized = true;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
#endif

        m_window = glfwCreateWindow((int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);
        m_context = new OpenGLContext(m_window);
        m_context->init();

        glfwSetWindowUserPointer(m_window, &m_data);
        setVSync(true);

        glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
            auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            data.width = width;
            data.height = height;

            WindowResizeEvent event{ static_cast<unsigned int>(width), static_cast<unsigned int>(height) };
            data.eventCallback(event);
        });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            WindowCloseEvent event;
            data.eventCallback(event);
        });

        glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            switch (action)
            {
            case GLFW_PRESS: {
                KeyPressedEvent event(key, 0);
                data.eventCallback(event);
                break;
            }

            case GLFW_RELEASE: {
                KeyReleasedEvent event(key);
                data.eventCallback(event);
                break;
            }

            case GLFW_REPEAT: {
                KeyPressedEvent event(key, 1);
                data.eventCallback(event);
                break;
            }
            }
        });

        glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int c) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            KeyTypedEvent event(c);
            data.eventCallback(event);
        });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            switch (action)
            {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(button);
                data.eventCallback(event);
                break;
            }

            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(button);
                data.eventCallback(event);
                break;
            }
            }
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
            data.eventCallback(event);
        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double x, double y) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            MouseMovedEvent event(static_cast<float>(x), static_cast<float>(y));
            data.eventCallback(event);
        });
    }

    void WindowImpl::shutdown()
    {
        glfwDestroyWindow(m_window);
    }

    void WindowImpl::onUpdate()
    {
        glfwPollEvents();
        m_context->swapBuffers();
    }

	void WindowImpl::setCursorVisible(bool visible)
	{
		assert(m_window != nullptr);
		glfwSetInputMode(m_window, GLFW_CURSOR, visible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);

		const auto oldVisible = m_data.cursorVisible;
		m_data.cursorVisible = visible;

		MouseCursorVisibilityChanged e{ m_data.cursorVisible };
		m_data.eventCallback(e);
	}

    void WindowImpl::setVSync(bool enabled)
    {
        glfwSwapInterval(enabled);
        m_data.vSync = enabled;
    }

    bool WindowImpl::isVSync() const
    {
        return m_data.vSync;
    }

	bool WindowImpl::isCursorVisible() const
	{
		return m_data.cursorVisible;
	}

    void* WindowImpl::getNativeWindow() const
    {
        return m_window;
    }

} // namespace butterfly
