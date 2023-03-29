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

                if (ImGui::TreeNodeEx(&tagComponent.tag, ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow, tagComponent.tag.c_str()))
                {
                    m_selected = entity;
                    ImGui::TreePop();
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
        }

        ImGui::End();
    }

} // namespace buterfly
