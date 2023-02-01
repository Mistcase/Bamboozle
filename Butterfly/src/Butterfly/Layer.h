#pragma once

#include "Butterfly/Core.h"
#include "Butterfly/Events/Event.h"

namespace butterfly
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate(float dt) {}
		virtual void onImGuiRender() {}
		virtual void onEvent(Event& event) {}

		inline const std::string& getName() const { return m_debugName; }
	protected:
		std::string m_debugName;
	};

} // namespace butterfly
