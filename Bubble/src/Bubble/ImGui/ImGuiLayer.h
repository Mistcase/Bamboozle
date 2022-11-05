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
		void onImGuiRender() override;

		void begin();
		void end();

	private:
		float m_time = 0.0f;
	};

} // namespace bubble