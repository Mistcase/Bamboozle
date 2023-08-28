#pragma once

#include "Bamboozle/Renderer/Shader.h"
#include "Core.h"
// #include "Events/ApplicationEvent.h"
// #include "Events/Event.h"
#include "ImGui/ImGuiLayer.h"
#include "LayerStack.h"
#include "Window.h"

class Window;
class WindowCloseEvent;

namespace bbzl
{
    class Camera;
    class IndexBuffer;
    class VertexBuffer;
    class VertexArray;

    class Application
    {
    public:
        Application(const std::string& name, const std::filesystem::path& resourcesPath);
        virtual ~Application();

        void run();
        void quit();

        void onEvent(Event& e);

        void pushLayer(Layer* layer);
        void pushOverlay(Layer* layer);

        inline static Application& GetInstance()
        {
            return *m_instance;
        }
        inline Window& getWindow()
        {
            return *m_window;
        }
        inline const std::filesystem::path& getResourceDirectory() const
        {
            return m_resourcesPath;
        }

    private:
        bool onWindowClose(WindowCloseEvent& e);
        bool onWindowResize(WindowResizeEvent& e);

    private:
        static Application* m_instance;

        std::unique_ptr<Window> m_window;
        LayerStack m_layerStack;
        ImGuiLayer* m_imGuiLayer;

        const std::filesystem::path m_resourcesPath;

    private:
        bool m_running = true;
        float m_time = 0.0f;
    };

    // Have to be defined by client
    Application* CreateApplication();

} // namespace bbzl
