#include "Editor.h"

#include "Butterfly/Renderer/Mesh.h"
#include "Butterfly/Renderer/Skybox.h"
#include "Butterfly/Transformable.h"
#include "Helpers.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <imgui.h>

namespace butterfly
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
        m_UITools.setScene(m_scene);

        std::vector<butterfly::Ref<butterfly::Texture>> textures{ butterfly::Texture2D::Create(helpers::MakePath("textures/wall.jpeg").generic_string()) };

        // Add objects to scene for test purposes.
        m_wall = m_scene->createEntity("Wall");
        m_wall.addComponent<MeshComponent>(MeshComponent::Create(helpers::MakePath("objects/scene.obj")));
        m_wall.addComponent<MaterialComponent>(Renderer::Shader(), MaterialComponent::LightingParams{ 0.2f, 0.3f, 1.0f, 20.0f }, std::move(textures));

        // m_directionalLight = m_scene->createEntity("GlobalLight");
        // m_directionalLight.addComponent<DirectionalLightComponent>(glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec3{ 0.0f, -1.0f, 0.0f });

        m_pointLight1 = m_scene->createEntity("Light1");
        m_pointLight1.addComponent<PointLightComponent>(glm::vec3{ 0.0f, 1.0f, 0.0f }, 2.5f);
        m_pointLight1.getComponent<TransformComponent>().setPosition({ 0.0f, 0.5f, 0.0f });

        // m_pointLight2 = m_scene->createEntity("Light2");
        // m_pointLight2.addComponent<PointLightComponent>(glm::vec3{ 1.0f, 0.0f, 0.0f }, 2.0f);
        // m_pointLight2.getComponent<TransformComponent>().setPosition({ -1.5f, 1.5f, 0.0f });

        // Create camera pawn and controller
        auto& window = butterfly::Application::GetInstance().getWindow();
        {
            // Create entity with camera component
            auto defaultCameraPawn = m_scene->createEntity("Default camera");
            auto& cameraComponent = defaultCameraPawn.addComponent<CameraComponent>();
            auto& transformComponent = defaultCameraPawn.getComponent<TransformComponent>();

            cameraComponent.projection = glm::perspective(glm::radians(45.0f), (float)window.getWidth() / window.getHeight(), 0.5f, 100.0f);
            cameraComponent.viewDirection = glm::normalize(glm::vec3{-1.0f, -1.0f, -1.0f});
            transformComponent.setPosition({ 3.0f, 4.0f, 15.0f });

            m_scene->setCameraPawn(defaultCameraPawn);
        }

        {
            auto camera2 = m_scene->createEntity("Camera2");
            auto& cameraComponent = camera2.addComponent<CameraComponent>();
            auto& transformComponent = camera2.getComponent<TransformComponent>();

            cameraComponent.projection = glm::perspective(glm::radians(45.0f), (float)window.getWidth() / window.getHeight(), 0.5f, 100.0f);
            cameraComponent.viewDirection = glm::normalize(glm::vec3{1.0f, 1.0f, 1.0f});
            transformComponent.setPosition({ 10.0f, 4.0f, 10.0f });
        }
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
        m_scene->onEvent(event);

        EventDispatcher dispatcher(event);
        dispatcher.dispatch<KeyReleasedEvent>([this](KeyEvent& e)
        {
            if (e.getKeyCode() == BUTTERFLY_KEY_ESCAPE)
            {
                if (Input::IsKeyPressed(BUTTERFLY_KEY_LEFT_SHIFT))
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
        const glm::vec2 viewportSize{ available.x, available.y };
        if (m_oldViewportSize != viewportSize)
        {
            BUTTERFLY_CORE_INFO("Resize viewport: {}x{}", viewportSize.x, viewportSize.y);

            m_framebuffer->resize(viewportSize.x, viewportSize.y);
            m_oldViewportSize = viewportSize;
        }

        const auto textureId = m_framebuffer->getColorAttachmentRendererId();
        ImGui::Image(reinterpret_cast<void*>(textureId), available, { 0.0f, 1.0f }, { 1.0f, 0.0f });
        ImGui::End();
    }

} // namespace butterfly
