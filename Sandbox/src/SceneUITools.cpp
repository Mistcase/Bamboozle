#include "SceneUITools.h"

#include "Butterfly/Transformable.h"
#include <Butterfly.h>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

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

                bool selected;
                if (ImGui::Selectable(tagComponent.tag.c_str(), &selected))
                {
                    m_selected = entity;
                }
            });
        }
        ImGui::End();
    }

    void SceneUITools::drawComponentsPanel()
    {
        constexpr size_t MaxStringLength = 64;

        ImGui::ShowDemoWindow();
        ImGui::Begin("Components");

        if (m_selected)
        {
            if (m_selected.hasComponent<TagComponent>())
            {
                ImGui::Text("Name");
                auto& component = m_selected.getComponent<TagComponent>();
                auto& tag = component.tag;

                char buf[MaxStringLength];
                ::memset(buf, 0, MaxStringLength);
                ::memcpy(buf, tag.c_str(), std::min(tag.size(), MaxStringLength - 1));

                ImGui::InputText("Tag", buf, MaxStringLength);
                tag = buf;
				ImGui::Separator();
            }

            if (m_selected.hasComponent<TransformComponent>())
            {
                ImGui::Text("Transform");
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
				ImGui::Separator();
            }

            if (m_selected.hasComponent<CameraComponent>())
            {
                ImGui::Text("Camera");
                auto controlledPawn = m_scene->m_cameraController.getPawn();
                auto& component = m_selected.getComponent<CameraComponent>();

                if (ImGui::Button("Possess", { 100.0f, 25.0f }))
                {
                    m_scene->m_cameraController.possess(m_selected);
                }

                ImGui::Separator();
            }

            if (m_selected.hasComponent<DirectionalLightComponent>())
            {
                static glm::vec3 newDirection;

                ImGui::Text("Light params");
                auto& component = m_selected.getComponent<DirectionalLightComponent>();

                ImGui::DragFloat3("Intensity", glm::value_ptr(component.intensity), 0.1f, 0.0f, 1.0f);
                ImGui::InputFloat3("Direction", glm::value_ptr(component.direction), "%.3f", ImGuiInputTextFlags_ReadOnly);
                ImGui::SameLine();
                if (ImGui::Button("Set"))
                {
                    ImGui::OpenPopup("Direction");
                    newDirection = component.direction;
                }

                if (ImGui::BeginPopupModal("Direction", NULL, ImGuiWindowFlags_AlwaysAutoResize))
                {
                    ImGui::DragFloat3("", glm::value_ptr(newDirection));
                    if (ImGui::Button("OK", ImVec2(140, 0)))
                    {
                        ImGui::CloseCurrentPopup(); component.direction = glm::normalize(newDirection);
                    }

                    ImGui::SetItemDefaultFocus();
                    ImGui::SameLine();

                    if (ImGui::Button("Cancel", ImVec2(140, 0)))
                    {
                        ImGui::CloseCurrentPopup();
                    }

                    ImGui::EndPopup();
                }

                ImGui::Separator();
            }

            if (m_selected.hasComponent<PointLightComponent>())
            {
                ImGui::Text("Light params");
                auto& component = m_selected.getComponent<PointLightComponent>();

                ImGui::DragFloat3("Intensity", glm::value_ptr(component.intensity), 0.1f, 0.0f, 1.0f);
                ImGui::DragFloat("Radius", &component.radius, 0.5f, 0.0f);
                ImGui::DragFloat("Linear", &component.attenuation.linearRatio, 0.1f);
                ImGui::DragFloat("Quadratic", &component.attenuation.quadraticRatio, 0.1f);
                ImGui::Separator();
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

} // namespace buterfly
