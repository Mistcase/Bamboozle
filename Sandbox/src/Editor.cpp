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
    m_camera->setPosition({ 7.0f, 8.0f, 10.0f });

    m_objects.push_back(std::make_shared<butterfly::SkyBox>(helpers::MakePath("objects/sphere.obj"), helpers::MakePath("textures/sky.jpeg"), m_camera.get()));
    m_skybox = m_objects.back().get();
    m_skybox->setScale({ 50.0f, 50.0f, 50.0f });

    m_objects.emplace_back(std::make_shared<butterfly::Object3D>(helpers::MakePath("objects/scene.obj")));
    auto scene = m_objects.back();

    m_pointLights.emplace_back(glm::vec3{ 0.0f, 1.0f, 0.0f }, 2.5f, glm::vec3{ 0.0f, 0.5f, 0.0f });
    m_pointLights.emplace_back(glm::vec3{ 1.0f, 0.0f, 0.0f }, 2.0f, glm::vec3{ -1.5f, 1.5f, 0.0f });
	m_directionalLights.emplace_back(glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec3{ 0.0f, -1.0f, 0.0f });

    std::vector<butterfly::Ref<butterfly::Texture>> textures{ butterfly::Texture2D::Create(helpers::MakePath("textures/wall.jpeg").generic_string()) };
    auto wallMaterial = butterfly::Material::Create(butterfly::Renderer::Shader(), { 0.12f, 0.3f, 1.0f, 20.0f }, std::move(textures));
    scene->setMaterial(wallMaterial);

    m_objects.emplace_back(std::make_shared<butterfly::Object3D>(helpers::MakePath("objects/barrel.obj")));
    m_barrel = m_objects.back().get();

    auto t1 = butterfly::Texture2D::Create(helpers::MakePath("textures/barrel/varil_low_lambert1_BaseColor.png"));
    auto t2 = butterfly::Texture2D::Create(helpers::MakePath("textures/barrel/varil_low_lambert1_Metallic.png"), butterfly::Texture2D::Format::RED);
    std::vector<butterfly::Ref<butterfly::Texture>> textures2{ t1, t2 };

    m_barrel->setMaterial(butterfly::Material::Create(butterfly::Renderer::Shader(), { 0.12f, 0.3f, 1.0f, 20.0f }, std::move(textures2)));
    m_barrel->setPosition({ 2.0f, 1.0f, 2.0f});
    m_barrel->setScale({ 0.4f, 0.4f, 0.4f });
}

void Editor::onDetach()
{
}

void Editor::onUpdate(float dt)
{
	if (m_isViewportFocused)
	{
		m_directionalLights.back().setDirection(glm::normalize(m_camera->getViewDirection()));
		Scene::update(dt);
	}

	m_framebuffer->bind();
	butterfly::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    butterfly::RenderCommand::Clear();

	Scene::render();
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
		m_isViewportFocused = ImGui::IsWindowFocused();

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
	m_cameraController->onEvent(event);

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
