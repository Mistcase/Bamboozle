#pragma once

#include "Core.h"
#include "Layer.h"

#include <vector>

namespace bubble 
{
	class BUBBLE_API LayerStack
	{
	public:
		using Container = std::vector<Layer*>;

	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

		Container::iterator begin() { return m_layers.begin(); }
		Container::iterator end() { return m_layers.end(); }
	private:
		Container m_layers;
		Container::iterator m_layerInsert;
	};

} // namespace bubble