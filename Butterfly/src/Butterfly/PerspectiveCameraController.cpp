#include "Butterfly/butterflypch.h"
#include "PerspectiveCameraController.h"

#include "Butterfly/Input.h"
#include "Butterfly/KeyCodes.h"
#include "Butterfly/Events/MouseEvent.h"
#include "Butterfly/Renderer/PerspectiveCamera.h"

namespace butterfly
{
	PerspectiveCameraController::PerspectiveCameraController(PerspectiveCamera* camera)
		: m_camera(camera)
	{
	}

	void PerspectiveCameraController::onUpdate(float dt)
	{
		const auto delta = dt;

		if (Input::IsKeyPressed(BUTTERFLY_KEY_W))
            m_camera->setPosition(m_camera->getPosition() + glm::vec3(0.0f, 0.0f, 5 * delta));

        if (Input::IsKeyPressed(BUTTERFLY_KEY_S))
            m_camera->setPosition(m_camera->getPosition() + glm::vec3(0.0f, 0.0f, 5 * -delta));
	}

	void PerspectiveCameraController::onEvent(Event& event)
	{
		// EventDispatcher dispatcher(event);
		// dispatcher.dispatch<MouseScrolledEvent>([this](MouseScrolledEvent& event){ return onMouseScrolled(event); });

		// const auto delta = event.getYOffset();

        // if (Input::IsKeyPressed(BUTTERFLY_KEY_LEFT_CONTROL))
        // {
        //     m_camera->setRotation(m_camera->getRotation() + 0.2f * delta);
        // }
        // else
        // {
        //     const auto zoom = m_camera->getZoom();
        //     const auto newZoom = zoom + 0.1f * delta;

        //     m_camera->setZoom(newZoom);
        // }

        // return true;
	}

} // namesapce butterfly
