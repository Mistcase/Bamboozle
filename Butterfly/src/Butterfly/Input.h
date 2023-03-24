#pragma once

#include "Butterfly/Core.h"

namespace butterfly
{
    class Input
    {
    public:
        inline static bool IsKeyPressed(int keycode)
        {
            return m_instance->isKeyPressedImpl(keycode);
        }

        inline static bool IsMouseButtonPressed(int button)
        {
            return m_instance->IsMouseButtonPressedImpl(button);
        }

        inline static std::pair<float, float> GetMousePosition()
        {
            return m_instance->getMousePositionImpl();
        }

        inline static bool GetMouseX()
        {
            return m_instance->getMouseXImpl();
        }

        inline static bool GetMouseY()
        {
            return m_instance->getMouseYImpl();
        }

    protected:
        virtual bool isKeyPressedImpl(int keycode) = 0;
        virtual bool IsMouseButtonPressedImpl(int button) = 0;
        virtual float getMouseXImpl() = 0;
        virtual float getMouseYImpl() = 0;

        virtual std::pair<float, float> getMousePositionImpl() = 0;

    private:
        static Input* m_instance;
    };

} // namespace butterfly
