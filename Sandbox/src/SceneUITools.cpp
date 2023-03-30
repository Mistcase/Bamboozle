#include "SceneUITools.h"

#include "Butterfly/Transformable.h"
#include <Butterfly.h>
#include <glm/gtc/type_ptr.hpp>

namespace butterfly
{
    void SceneUITools::setScene(const Ref<Scene>& scene)
    {
        m_scene = scene;
    }

    void SceneUITools::onImGuiRender()
    {
        drawHierarchyPanel();
        drawComponentsPanel();
        drawStatusPanel();
    }

    void SceneUITools::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<KeyReleasedEvent>([this](KeyReleasedEvent& event)
        {
            if (event.getKeyCode() == BUTTERFLY_KEY_TAB)
            {
                auto& camera = m_scene->m_cameraController;
                camera.blockInput(!camera.isInputBlocked());
            }
            return false;
        });
    }

    void SceneUITools::drawHierarchyPanel()
    {
        assert(m_scene != nullptr);

        ImGui::Begin("Hierarchy panel");
        {
            m_scene->m_registry.each([this](auto nativeHandle)
            {
                Entity entity { nativeHandle, &m_scene->m_registry };
                const auto& tagComponent = entity.getComponent<TagComponent>();

                if (ImGui::Selectable(tagComponent.tag.c_str()))
                {
					if (Input::IsKeyPressed(BUTTERFLY_KEY_LEFT_SHIFT))
					{
						m_scene->m_registry.destroy(nativeHandle);
					}
					else
					{
						m_selected = entity;
					}
                }
            });

            ImGui::Separator();
            if (ImGui::Button("Add entity", { 120.0f, 25.0f }))
            {
                ImGui::OpenPopup("NewEntity");
                memset(m_newEntityName, 0, MaxStringLength);
            }

            if (ImGui::BeginPopupModal("NewEntity", NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                showNewEntityPopup();
            }

            ImGui::End();
        }
    }

    void SceneUITools::drawComponentsPanel()
    {
        ImGui::ShowDemoWindow();
        ImGui::Begin("Components");

        if (m_selected)
        {
			showComponent<TagComponent>([this]()
			{
				auto& component = m_selected.getComponent<TagComponent>();
                auto& tag = component.tag;

                char buf[MaxStringLength];
                ::memset(buf, 0, MaxStringLength);
                ::memcpy(buf, tag.c_str(), std::min(tag.size(), MaxStringLength - 1));

                ImGui::InputText("Tag", buf, MaxStringLength);
                tag = buf;
			}, "Name");

			showComponent<TransformComponent>([this]()
			{
				auto& component = m_selected.getComponent<TransformComponent>();

                auto position = component.getPosition();
                auto rotation = glm::degrees(glm::eulerAngles(component.getRotation()));
                auto scale = component.getScale();

                ImGui::DragFloat3("Position", glm::value_ptr(position));
                ImGui::DragFloat3("Rotation", glm::value_ptr(rotation));
                ImGui::DragFloat3("Scale", glm::value_ptr(scale));

                component.setPosition(position);
                component.setRotation(glm::radians(rotation));
                component.setScale(scale);
			}, "Transform");

			showComponent<CameraComponent>([this]()
			{
				auto controlledPawn = m_scene->m_cameraController.getPawn();
                auto& component = m_selected.getComponent<CameraComponent>();

                if (ImGui::Button("Possess", { 100.0f, 25.0f }))
                {
                    m_scene->m_cameraController.possess(m_selected);
                }
			});

			showComponent<DirectionalLightComponent>([this]()
			{
				auto& component = m_selected.getComponent<DirectionalLightComponent>();

                ImGui::DragFloat3("Intensity", glm::value_ptr(component.intensity), 0.1f, 0.0f, 1.0f);
                ImGui::InputFloat3("Direction", glm::value_ptr(component.direction), "%.3f", ImGuiInputTextFlags_ReadOnly);
                ImGui::SameLine();
                if (ImGui::Button("Set"))
                {
                    ImGui::OpenPopup("Direction");
					m_newLightDirection = { 0.0f, 0.0f, 0.0f };
                }
                if (ImGui::BeginPopupModal("Direction", NULL, ImGuiWindowFlags_AlwaysAutoResize))
                {
                    showSetDirectionPopup(component);
                }
			}, "Directional light");

			showComponent<PointLightComponent>([this]()
			{
				auto& component = m_selected.getComponent<PointLightComponent>();

                ImGui::DragFloat3("Intensity", glm::value_ptr(component.intensity), 0.1f, 0.0f, 1.0f);
                ImGui::DragFloat("Radius", &component.radius, 0.5f, 0.0f);
                ImGui::DragFloat("Linear", &component.attenuation.linearRatio, 0.1f);
                ImGui::DragFloat("Quadratic", &component.attenuation.quadraticRatio, 0.1f);
			}, "Point light");

            if (ImGui::BeginMenu("Add component"))
            {
                showComponentsMenu();
                ImGui::EndMenu();
            }
        }

        ImGui::End();
    }

    void SceneUITools::drawStatusPanel()
    {
        ImGui::Begin("Status");

        // Camera
        auto blockInput = m_scene->m_cameraController.isInputBlocked();
        ImGui::Text("ActiveCamera: %s", m_scene->m_cameraController.getPawn().getComponent<TagComponent>().tag.c_str());
        ImGui::Checkbox("Block camera input (Tab)", &blockInput);
        m_scene->m_cameraController.blockInput(blockInput);

        ImGui::End();
    }

    void SceneUITools::showSetDirectionPopup(DirectionalLightComponent& component)
    {
        ImGui::DragFloat3("", glm::value_ptr(m_newLightDirection));
        if (ImGui::Button("OK", ImVec2(140, 0)))
        {
            ImGui::CloseCurrentPopup();
            component.direction = glm::normalize(m_newLightDirection);
        }

        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();

        if (ImGui::Button("Cancel", ImVec2(140, 0)))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    void SceneUITools::showNewEntityPopup()
    {
		if (ImGui::IsRootWindowOrAnyChildFocused() && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0))
		{
			ImGui::SetKeyboardFocusHere(0);
		}

        ImGui::InputText("Entity", m_newEntityName, MaxStringLength);
        if (ImGui::Button("OK", ImVec2(140, 0)))
        {
            ImGui::CloseCurrentPopup();
			m_selected = m_scene->createEntity(m_newEntityName);
        }

        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();

        if (ImGui::Button("Cancel", ImVec2(140, 0)))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    void SceneUITools::showComponentsMenu()
    {
        if (!m_selected.hasComponent<PointLightComponent>() && ImGui::MenuItem("Point light source"))
        {
            m_selected.addComponent<PointLightComponent>(glm::vec3{ 1.0f, 1.0f, 1.0f }, 1.0f);
        }

		if (!m_selected.hasComponent<DirectionalLightComponent>() && ImGui::MenuItem("Directional light source"))
		{
			m_selected.addComponent<DirectionalLightComponent>(glm::vec3{ 1.0f, 1.0f, 1.0f }, glm::vec3{ 0.0f, -1.0f, 0.0f });
		}
    }

} // namespace buterfly
