#include "bubblepch.h"
#include "ImGuiLayer.h"

#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

#include "Bubble/Application.h"

#include "GLFW/glfw3.h"
#include <glad/glad.h>

namespace bubble
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::onAttach()
	{
		ImGui::CreateContext();
  		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TEMPORARY: should eventually use Bubble key codes
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::onDetach()
	{
	}

	void ImGuiLayer::onUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		auto& app = Application::GetInstance();
		io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
		m_time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::onEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.dispatch<MouseButtonPressedEvent>([this](auto& e) { return onMouseButtonPressed(e); });
		dispatcher.dispatch<MouseButtonReleasedEvent>([this](auto& e) { return onMouseButtonReleased(e); });
		dispatcher.dispatch<MouseMovedEvent>([this](auto& e) { return onMouseMoved(e); });
		dispatcher.dispatch<MouseScrolledEvent>([this](auto& e) { return onMouseScrolled(e); });

		dispatcher.dispatch<KeyPressedEvent>([this](auto& e) { return onKeyPressed(e); });
		dispatcher.dispatch<KeyReleasedEvent>([this](auto& e) { return onKeyReleased(e); });
		dispatcher.dispatch<KeyTypedEvent>([this](auto& e) { return onKeyTyped(e); });

		dispatcher.dispatch<WindowResizeEvent>([this](auto& e) { return onWindowResize(e); });
	}

	bool ImGuiLayer::onMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		auto& io = ImGui::GetIO();
		io.MouseDown[e.getMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::onMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		auto& io = ImGui::GetIO();
		io.MouseDown[e.getMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::onMouseMoved(MouseMovedEvent& e)
	{
		auto& io = ImGui::GetIO();
		io.MousePos = { e.getX(), e.getY() };

		return false;
	}

	bool ImGuiLayer::onMouseScrolled(MouseScrolledEvent& e)
	{
		auto& io = ImGui::GetIO();
		io.MouseWheelH += e.getXOffset();
		io.MouseWheel += e.getYOffset();

		return false;
	}

	bool ImGuiLayer::onKeyPressed(KeyPressedEvent& e)
	{
		auto& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool ImGuiLayer::onKeyReleased(KeyReleasedEvent& e)
	{
		auto& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::onKeyTyped(KeyTypedEvent& e)
	{
		auto& io = ImGui::GetIO();
		const auto c = e.GetKeyCode();
		if (c > 0 && c < 0x10000)
			io.AddInputCharacter(static_cast<unsigned short>(c));

		return false;
	}

	bool ImGuiLayer::onWindowResize(WindowResizeEvent& e)
	{
		auto& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.getWidth(), e.getHeight());
		io.DisplayFramebufferScale = { 1.0f, 1.0f };
		glViewport(0, 0, e.getWidth(), e.getHeight());

		return false;
	}

} // namespace bubble