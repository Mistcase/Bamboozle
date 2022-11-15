#pragma once

#include <functional>

namespace bubble
{
    class Camera;
    class Event;
    class MouseScrolledEvent;

    class CameraController
    {
    public:
        CameraController(Camera* camera);

        void onUpdate(float dt);
        void onEvent(Event& event);

    private:
        bool onMouseScrolled(bubble::MouseScrolledEvent& event);

    private:
        Camera* m_camera;
        float m_speed = 1.0f;
    };

} // namespace bubble
