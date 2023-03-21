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

		if (Input::IsKeyPressed(BUTTERFLY_KEY_A))
            m_camera->setPosition(m_camera->getPosition() + glm::vec3(5 * delta, 0.0f, 0.0f));

		if (Input::IsKeyPressed(BUTTERFLY_KEY_D))
            m_camera->setPosition(m_camera->getPosition() + glm::vec3(5 * -delta, 0.0f, 0.0f));

		m_camera->update();
	}

	void PerspectiveCameraController::onEvent(Event& event)
	{
	}

} // namesapce butterfly
