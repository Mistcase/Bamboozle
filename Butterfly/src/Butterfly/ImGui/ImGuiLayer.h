#pragma once

#include "Butterfly/Layer.h"

#include "Butterfly/Events/ApplicationEvent.h"
#include "Butterfly/Events/KeyEvent.h"
#include "Butterfly/Events/MouseEvent.h"

namespace butterfly
{
	class ImGuiLayer : public Layer
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

} // namespace butterfly
