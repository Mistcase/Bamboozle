#include "Butterfly/butterflypch.h"
#include "CameraController.h"

#include "Butterfly/Input.h"
#include "Butterfly/KeyCodes.h"
#include "Butterfly/Events/MouseEvent.h"
#include "Butterfly/Renderer/Camera.h"

namespace butterfly
{
    CameraController::CameraController(Camera* camera)
        : m_camera(camera)
    {
    }

    void CameraController::onUpdate(float dt)
    {
        const auto delta = 100.0f * dt * m_camera->getZoom();

        if (Input::IsKeyPressed(BUTTERFLY_KEY_W))
            m_camera->setPosition(m_camera->getPosition() + glm::vec3(0.0f, delta, 0.0f));

        if (Input::IsKeyPressed(BUTTERFLY_KEY_S))
            m_camera->setPosition(m_camera->getPosition() + glm::vec3(0.0f, -delta, 0.0f));

        if (Input::IsKeyPressed(BUTTERFLY_KEY_D))
            m_camera->setPosition(m_camera->getPosition() + glm::vec3(delta, 0.0f, 0.0f));

        if (Input::IsKeyPressed(BUTTERFLY_KEY_A))
            m_camera->setPosition(m_camera->getPosition() + glm::vec3(-delta, 0.0f, 0.0f));
    }

    void CameraController::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseScrolledEvent>([this](MouseScrolledEvent& event){ return onMouseScrolled(event); });
    }

    bool CameraController::onMouseScrolled(butterfly::MouseScrolledEvent& event)
    {
        const auto delta = event.getYOffset();

        if (Input::IsKeyPressed(BUTTERFLY_KEY_LEFT_CONTROL))
        {
            m_camera->setRotation(m_camera->getRotation() + 0.2f * delta);
        }
        else
        {
            const auto zoom = m_camera->getZoom();
            const auto newZoom = zoom + 0.1f * delta;

            m_camera->setZoom(newZoom);
        }

        return true;
    }

} // namespace butterfly
