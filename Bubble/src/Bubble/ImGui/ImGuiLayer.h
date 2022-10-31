#pragma once

#include "Bubble/Layer.h"

#include "Bubble/Events/ApplicationEvent.h"
#include "Bubble/Events/KeyEvent.h"
#include "Bubble/Events/MouseEvent.h"

namespace bubble
{
	class BUBBLE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach() override;
		void onDetach() override;
		
		void onUpdate() override;
		void onEvent(Event& event) override;

	private:
		bool onMouseButtonPressed(MouseButtonPressedEvent& e);
		bool onMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool onMouseMoved(MouseMovedEvent& e);
		bool onMouseScrolled(MouseScrolledEvent& e);
		bool onKeyPressed(KeyPressedEvent& e);
		bool onKeyReleased(KeyReleasedEvent& e);
		bool onKeyTyped(KeyTypedEvent& e);
		bool onWindowResize(WindowResizeEvent& e);

	private:
		float m_time = 0.0f;
	};

} // namespace bubble