#include "bbzlpch.h"
#include "CameraController.h"

#include "Bamboozle/Events/MouseEvent.h"
#include "Bamboozle/Input.h"
#include "Bamboozle/KeyCodes.h"
#include "Bamboozle/Renderer/OrthographicCamera.h"
#include "Bamboozle/bbzl.h"

namespace bbzl
{
    CameraController::CameraController()
        : m_camera(nullptr)
    {
    }

    void CameraController::onUpdate(float dt)
    {
//        const auto delta = 100.0f * dt * m_camera->getZoom();
//
//        if (Input::IsKeyPressed(BBZL_KEY_W))
//            m_camera->setPosition(m_camera->getPosition() + glm::vec3(0.0f, delta, 0.0f));
//
//        if (Input::IsKeyPressed(BBZL_KEY_S))
//            m_camera->setPosition(m_camera->getPosition() + glm::vec3(0.0f, -delta, 0.0f));
//
//        if (Input::IsKeyPressed(BBZL_KEY_D))
//            m_camera->setPosition(m_camera->getPosition() + glm::vec3(delta, 0.0f, 0.0f));
//
//        if (Input::IsKeyPressed(BBZL_KEY_A))
//            m_camera->setPosition(m_camera->getPosition() + glm::vec3(-delta, 0.0f, 0.0f));
    }

    void CameraController::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseScrolledEvent>([this](MouseScrolledEvent& event) { return onMouseScrolled(event); });
    }

    bool CameraController::onMouseScrolled(bbzl::MouseScrolledEvent& event)
    {
        const auto delta = event.getYOffset();

//        if (Input::IsKeyPressed(BBZL_KEY_LEFT_CONTROL))
//        {
//            m_camera->setRotation(m_camera->getRotation() + 0.2f * delta);
//        }
//        else
//        {
//            const auto zoom = m_camera->getZoom();
//            const auto newZoom = zoom + 0.1f * delta;
//
//            m_camera->setZoom(newZoom);
//        }

        return true;
    }

} // namespace bbzl
