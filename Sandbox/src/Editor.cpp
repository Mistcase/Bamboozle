#include "Editor.h"

#include "Butterfly/Renderer/Skybox.h"
#include "Helpers.h"
#include <imgui.h>

Editor::Editor()
	: Layer("EditorLayer")
	, m_window(butterfly::Application::GetInstance().getWindow())
{
	const auto& window = butterfly::Application::GetInstance().getWindow();
	m_framebuffer = butterfly::Framebuffer::Create({ window.getWidth(), window.getHeight(), 1, true });
}

void Editor::onAttach()
{
	struct ScriptableThing : public butterfly::ScriptableEntity
	{
		void onCreate()
		{
			BUTTERFLY_CORE_INFO("On create!");
		}

		void onUpdate(float dt)
		{
			static size_t counter = 0;
			counter++;

			if (counter <= 5)
			{
				BUTTERFLY_CORE_INFO("On update!");
			}
		}

		void onDestroy()
		{
			BUTTERFLY_CORE_INFO("On destroy!");
		}
	};

	auto entity = m_scene.createEntity("Test");
    entity.addComponent<butterfly::NativeScriptComponent>().bind<ScriptableThing>();
}

void Editor::onDetach()
{
}

void Editor::onUpdate(float dt)
{
	m_scene.update(dt);

	m_framebuffer->bind();
	m_scene.render();
	m_framebuffer->unbind();
}

void Editor::onImGuiRender()
{
	static bool dockspaceOpen = true;
	static bool opt_fullscreen_persistant = true;
    static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
    bool opt_fullscreen = opt_fullscreen_persistant;

    // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // because it would be confusing to have two docking targets within each others.
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    if (opt_fullscreen)
    {
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    }

    // When using ImGuiDockNodeFlags_PassthruDockspace, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
    if (opt_flags & ImGuiDockNodeFlags_PassthruDockspace)
        window_flags |= ImGuiWindowFlags_NoBackground;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
    ImGui::PopStyleVar();

    if (opt_fullscreen)
        ImGui::PopStyleVar(2);

    // Dockspace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
    }

    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
			{
				butterfly::Application::GetInstance().quit();
			}

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

	ImGui::Begin("Objects");
	{
		const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_AllowItemOverlap;
		bool nodeOpen = ImGui::TreeNodeEx("Camera", flags);
		if (nodeOpen)
		{
			ImGui::TreePop();
		}
	}
	ImGui::End();

	ImGui::Begin("Viewport");
	{
		m_isViewportFocused = ImGui::IsWindowFocused() && ImGui::IsWindowHovered();

		const auto available = ImGui::GetContentRegionAvail();
		const glm::vec2 viewportSize{ available.x, available.y };
		if (m_oldViewportSize != viewportSize)
		{
			BUTTERFLY_CORE_INFO("Resize viewport: {}x{}", viewportSize.x, viewportSize.y);

			m_framebuffer->resize(viewportSize.x, viewportSize.y);
			m_oldViewportSize = viewportSize;
		}

		const auto textureId = m_framebuffer->getColorAttachmentRendererId();
		ImGui::Image(reinterpret_cast<void*>(textureId), available, { 0.0f, 1.0f }, { 1.0f, 0.0f });
	}
	ImGui::End();

    ImGui::End();
}

void Editor::onEvent(butterfly::Event& event)
{
	// m_cameraController->onEvent(event);

	if (event.getEventType() == butterfly::EventType::KeyReleased)
	{
		butterfly::EventDispatcher dispatcher(event);
		dispatcher.dispatch<butterfly::KeyReleasedEvent>([this](butterfly::KeyEvent& e)
		{
			if (e.getKeyCode() == BUTTERFLY_KEY_ESCAPE)
			{
				if (butterfly::Input::IsKeyPressed(BUTTERFLY_KEY_LEFT_SHIFT))
				{
					butterfly::Application::GetInstance().quit();
				}
				else
				{
					m_window.setCursorVisible(!m_window.isCursorVisible());
				}
			}
			return true;
		});
	}
}
