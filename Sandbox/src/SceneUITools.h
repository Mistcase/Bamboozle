#pragma once

#include <Butterfly.h>
#include <imgui.h>

namespace butterfly
{
    class Scene;

    class SceneUITools
    {
    public:
        void setScene(const Ref<Scene>& scene);
        void onImGuiRender();

        void onEvent(Event& event);

    private:
        void drawHierarchyPanel();
        void drawComponentsPanel();
        void drawStatusPanel();

        void showSetDirectionPopup(DirectionalLightComponent& component);
        void showNewEntityPopup();

        void showComponentsMenu();

		template <typename Component>
		void showComponent(std::function<void()> showFunc, const char* name = typeid(Component).name())
		{
			if (m_selected.hasComponent<Component>())
            {
                ImGui::Text(name);
				showFunc();
				ImGui::Separator();
            }
		}

    private:
        Ref<Scene> m_scene;
        Entity m_selected;

    private:
        static const size_t MaxStringLength = 64;
        glm::vec3 m_newLightDirection;
        char m_newEntityName[MaxStringLength];
    };
} // namespace butterfly
