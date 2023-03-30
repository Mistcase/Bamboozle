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

		void onViewportChanged(glm::vec2 viewportSize);

    private:
        void drawHierarchyPanel();
        void drawComponentsPanel();
        void drawStatusPanel();

		void openSetVec3Popup();
        void showSetVec3Popup(glm::vec3& value);

		void openNewEntityPopup();
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
        glm::vec3 m_newVec3;
        char m_newEntityName[MaxStringLength];

		bool m_isNewEntityRequired = false;
    };
} // namespace butterfly
