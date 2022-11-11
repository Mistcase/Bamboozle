#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Window.h"

#include "ImGui/ImGuiLayer.h"
#include "Bubble/Renderer/Shader.h"

class WindowCloseEvent;

namespace bubble
{
    class IndexBuffer;
    class VertexBuffer;
    class VertexArray;

	class BUBBLE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void onEvent(Event& e);

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* layer);

	    inline static Application& GetInstance() { return *m_instance; }
		inline Window& getWindow() { return *m_window; }

	private:
		bool onWindowClose(WindowCloseEvent& e);

	private:
		static Application* m_instance;

		std::unique_ptr<Window> m_window;
		ImGuiLayer* m_imGuiLayer;
		bool m_running = true;

        std::shared_ptr<Shader> m_shader;
        std::shared_ptr<VertexBuffer> m_vertexBuffer;
        std::shared_ptr<IndexBuffer> m_indexBuffer;
        std::shared_ptr<VertexArray> m_vertexArray;
        std::shared_ptr<VertexArray> m_squareVA;

		LayerStack m_layerStack;
	};

	// Have to be defined by client
	Application* CreateApplication();

} // namespace bubble
