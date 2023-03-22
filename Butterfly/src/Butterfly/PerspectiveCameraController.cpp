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
            m_camera->setPosition(m_camera->getPosition() + 0.25f * m_camera->getViewDirection());

        if (Input::IsKeyPressed(BUTTERFLY_KEY_S))
            m_camera->setPosition(m_camera->getPosition() - 0.25f * m_camera->getViewDirection());

		if (Input::IsKeyPressed(BUTTERFLY_KEY_A))
		{
			const auto right = glm::cross(m_camera->getViewDirection(), glm::vec3(0.0f, 1.0f, 0.0f));
			m_camera->setPosition(m_camera->getPosition() - 0.25f * right);
		}

		if (Input::IsKeyPressed(BUTTERFLY_KEY_D))
		{
			const auto right = glm::cross(m_camera->getViewDirection(), glm::vec3(0.0f, 1.0f, 0.0f));
			m_camera->setPosition(m_camera->getPosition() + 0.25f * right);
		}

		m_camera->update();
	}

	void PerspectiveCameraController::onEvent(Event& event)
	{
		const auto& e = static_cast<MouseMovedEvent&>(event);
		if (event.getEventType() == EventType::MouseMoved)
		{
			static bool firstTime = true;
			static glm::vec2 oldPos;

			if (!firstTime)
			{
                const auto delta = oldPos - glm::vec2{ e.getX(), e.getY() };
                const auto viewDirection = m_camera->getViewDirection();
                const auto right = glm::cross(viewDirection, { 0.0f, 1.0f, 0.0f });

                auto quat1 = glm::angleAxis(delta.y / 200.0f, right);
                auto quat2 = glm::angleAxis(delta.x / 200.0f, glm::vec3{ 0.0, 1.0f, 0.0f });

                auto newRotation = quat1 * quat2 * m_camera->getRotation();
                m_camera->setRotation(newRotation);
			}

			firstTime = false;
			oldPos = { e.getX(), e.getY() };
		}
	}

} // namesapce butterfly
