#include "Bamboozle/bbzlpch.h"
#include "Editor.h"

#include "Bamboozle/Renderer/Mesh.h"
#include "Bamboozle/Renderer/Skybox.h"
#include "Bamboozle/Transformable.h"
#include "Helpers.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <imgui.h>

namespace bbzl
{
    EditorLayer::EditorLayer()
        : Layer("EditorLayerLayer")
        , m_window(Application::GetInstance().getWindow())
        , m_scene(std::make_shared<Scene>())
    {
        const auto& window = Application::GetInstance().getWindow();
        m_framebuffer = Framebuffer::Create({ window.getWidth(), window.getHeight(), 1, true });
    }

    void EditorLayer::onAttach()
    {
        // m_UITools.setScene(m_scene);
    }

    void EditorLayer::onDetach()
    {
    }

    void EditorLayer::onUpdate(float dt)
    {
        m_scene->update(dt);

        m_framebuffer->bind();
        m_scene->render();
        m_framebuffer->unbind();
    }

    void EditorLayer::onImGuiRender()
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

        drawImGuiMenuBar();
        drawImGuiViewport();
        m_UITools.onImGuiRender();

        ImGui::End();
    }

    void EditorLayer::onEvent(Event& event)
    {
        m_UITools.onEvent(event);

		if (!m_window.isCursorVisible())
		{
			m_scene->onEvent(event);
		}

        EventDispatcher dispatcher(event);
        dispatcher.dispatch<KeyReleasedEvent>([this](KeyEvent& e)
        {
            if (e.getKeyCode() == BBZL_KEY_ESCAPE)
            {
                if (Input::IsKeyPressed(BBZL_KEY_LEFT_SHIFT))
                {
                    Application::GetInstance().quit();
                }
                else
                {
                    m_window.setCursorVisible(!m_window.isCursorVisible());
                }
            }
            return true;
        });
    }

    void EditorLayer::drawImGuiMenuBar()
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit"))
                {
                    Application::GetInstance().quit();
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }
    }

    void EditorLayer::drawImGuiViewport()
    {
        ImGui::Begin("Viewport");
        m_isViewportFocused = ImGui::IsWindowFocused() && ImGui::IsWindowHovered();

        const auto available = ImGui::GetContentRegionAvail();
        const glm::vec2 viewportSize{ std::max(available.x, 1.0f), std::max(available.y, 1.0f) };
        if (m_oldViewportSize != viewportSize)
        {
            BBZL_CORE_INFO("Resize viewport: {}x{}", viewportSize.x, viewportSize.y);
            m_framebuffer->resize(viewportSize.x, viewportSize.y);
            m_oldViewportSize = viewportSize;

			m_UITools.onViewportChanged(viewportSize);
        }

        const auto textureId = m_framebuffer->getColorAttachmentRendererId();
        ImGui::Image(reinterpret_cast<void*>(textureId), available, { 0, 1 }, { 1, 0 });
        ImGui::End();
    }

} // namespace bbzl
