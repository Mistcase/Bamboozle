
#include "Sandbox2D.h"

#include <imgui.h>

Sandbox2DLayer::Sandbox2DLayer()
    : Layer("Sandbox2DLayer")
{
}

void Sandbox2DLayer::onAttach()
{
    auto& window = butterfly::Application::GetInstance().getWindow();

    m_camera = std::make_unique<butterfly::Camera>(window.getWidth(), window.getHeight());
    m_cameraController = std::make_unique<butterfly::CameraController>(m_camera.get());

    m_texture = butterfly::Texture2D::Create("/Users/ivan/dev/Projects/Butterfly/Sandbox/assets/Checkerboard.png");
    m_texture2 = butterfly::Texture2D::Create("/Users/ivan/dev/Projects/Butterfly/Sandbox/assets/smoke.png");

    butterfly::FramebufferSpecification fbSpec;
    fbSpec.width = 1280;
    fbSpec.height = 720;
    // m_framebuffer = butterfly::Framebuffer::Create(fbSpec);
}

void Sandbox2DLayer::onDetach()
{
}

void Sandbox2DLayer::onUpdate(float dt)
{
    m_cameraController->onUpdate(dt);

    //m_framebuffer->bind();

    butterfly::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    butterfly::RenderCommand::Clear();

    butterfly::Renderer2D::BeginScene(m_camera.get());
    butterfly::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 250.0f, 250.0f }, glm::radians(45.0f), { 1.0f, 0.0f, 0.0f, 1.0f }, m_texture);
    butterfly::Renderer2D::DrawQuad({ 300.0f, 300.0f, -0.1f }, { 250.0f, 250.0f }, 0.0f, { 0.0f, 0.0f, 1.0f, 1.0f }, m_texture2 );
    butterfly::Renderer2D::DrawQuad({ -300.0f, -300.0f, -0.1f }, { 250.0f, 250.0f }, { 0.0f, 1.0f, 0.0f, 1.0f });

    butterfly::Renderer2D::EndScene();
    // m_framebuffer->unbind();
}

void Sandbox2DLayer::onImGuiRender()
{
    // static bool opt_fullscreen_persistant = true;
    // static ImGuiDockNodeFlags opt_flags = ImGuiDockNodeFlags_None;
    // bool opt_fullscreen = opt_fullscreen_persistant;

    // // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
    // // because it would be confusing to have two docking targets within each others.
    // ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    // if (opt_fullscreen)
    // {
    //     ImGuiViewport* viewport = ImGui::GetMainViewport();
    //     ImGui::SetNextWindowPos(viewport->Pos);
    //     ImGui::SetNextWindowSize(viewport->Size);
    //     ImGui::SetNextWindowViewport(viewport->ID);
    //     ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    //     ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    //     window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    //     window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    // }

    // // When using ImGuiDockNodeFlags_PassthruDockspace, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
    // if (opt_flags & ImGuiDockNodeFlags_PassthruDockspace)
    //     window_flags |= ImGuiWindowFlags_NoBackground;

    // static bool p_open = true;

    // ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    // ImGui::Begin("DockSpace Demo", &p_open, window_flags);
    // ImGui::PopStyleVar();

    // if (opt_fullscreen)
    //     ImGui::PopStyleVar(2);

    // // Dockspace
    // ImGuiIO& io = ImGui::GetIO();
    // if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    // {
    //     ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
    //     ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), opt_flags);
    // }

    // if (ImGui::BeginMenuBar())
    // {
    //     if (ImGui::BeginMenu("File"))
    //     {
    //         if (ImGui::MenuItem("Quit", NULL, false, true))
    //             butterfly::Application::GetInstance().quit();
    //         ImGui::EndMenu();
    //     }

    //     ImGui::EndMenuBar();
    // }

    // ImGui::Begin("Scene");
    // const auto textureId = m_framebuffer->getColorAttachmentRendererId();
    // ImGui::Image((void*)textureId, ImVec2{ 256.0f, 256.0f });
    // ImGui::End();

    // ImGui::End();
}

void Sandbox2DLayer::onEvent(butterfly::Event& event)
{
    m_cameraController->onEvent(event);

    butterfly::EventDispatcher dispatcher(event);
    dispatcher.dispatch<butterfly::KeyReleasedEvent>([this](butterfly::KeyEvent& e){ return onKeyEvent(e); });
    dispatcher.dispatch<butterfly::WindowResizeEvent>([this](butterfly::WindowResizeEvent& e)
    {
        m_camera->setSize(e.getWidth(), e.getHeight());
        return true;
    });
}

bool Sandbox2DLayer::onKeyEvent(const butterfly::KeyEvent& event)
{
    if (event.getKeyCode() == BUTTERFLY_KEY_ESCAPE)
    {
        butterfly::Application::GetInstance().quit();
        return true;
    }

    return false;
}
