#pragma once

#include "Core.h"
#include "Layer.h"
#include <vector>

namespace bbzl
{
    class LayerStack
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

        Container::iterator begin()
        {
            return m_layers.begin();
        }
        Container::iterator end()
        {
            return m_layers.end();
        }
        Container::reverse_iterator rbegin()
        {
            return m_layers.rbegin();
        }
        Container::reverse_iterator rend()
        {
            return m_layers.rend();
        }

    private:
        Container m_layers;
        size_t m_layerInsertIndex = 0;
    };

} // namespace bbzl
