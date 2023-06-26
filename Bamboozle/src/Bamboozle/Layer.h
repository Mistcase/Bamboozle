#pragma once

#include "Bamboozle/Core.h"
#include "Bamboozle/Events/Event.h"

namespace bbzl
{
    class Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void onAttach()
        {
        }
        virtual void onDetach()
        {
        }
        virtual void onUpdate(float dt)
        {
        }
        virtual void onImGuiRender()
        {
        }
        virtual void onEvent(Event& event)
        {
        }

        inline const std::string& getName() const
        {
            return m_debugName;
        }

    protected:
        std::string m_debugName;
    };

} // namespace bbzl
