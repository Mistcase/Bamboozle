#include "Bamboozle/bbzl.h"
#include "PerspectiveCamera.h"

#include "Bamboozle/Log.h"
#include "Bamboozle/Scene/Components.h"
#include "Bamboozle/Transformable.h" // TODO: Rename as TransformComponent
#include "Bamboozle/Events/Event.h"
#include "Bamboozle/Events/MouseEvent.h"
#include "Bamboozle/Input.h"
#include "Bamboozle/KeyCodes.h"

namespace bbzl
{
	void PerspectiveCamera::possess(Entity entity)
	{
		m_entity = entity;
		updateViewProjection();
	}

    void PerspectiveCamera::blockInput(bool block)
    {
        m_blockInput = block;
		if (m_blockInput)
		{
			m_oldCursorValid = false;
		}
    }

    void PerspectiveCamera::update(float dt)
    {
        const auto delta = 10.0f * dt;

        auto& camera = m_entity.getComponent<CameraComponent>();
		auto& transform = m_entity.getComponent<TransformComponent>();

        if (!m_blockInput)
        {
            if (Input::IsKeyPressed(BBZL_KEY_W))
            {
                transform.setPosition(transform.getPosition() + delta * camera.viewDirection);
            }

            if (Input::IsKeyPressed(BBZL_KEY_S))
            {
                transform.setPosition(transform.getPosition() - delta * camera.viewDirection);
            }

            if (Input::IsKeyPressed(BBZL_KEY_A))
            {
                const auto right = glm::cross(camera.viewDirection, glm::vec3(0.0f, 1.0f, 0.0f));
                transform.setPosition(transform.getPosition() - delta * right);
            }

            if (Input::IsKeyPressed(BBZL_KEY_D))
            {
                const auto right = glm::cross(camera.viewDirection, glm::vec3(0.0f, 1.0f, 0.0f));
                transform.setPosition(transform.getPosition() + delta * right);
            }
        }

        // TODO: FIXME, subscribe to transform changed!
		camera.viewDirection = glm::normalize(glm::rotate(transform.getRotation(), glm::vec3{ 0.0f, 0.0f, -1.0f}));
        updateViewProjection();
    }

    void PerspectiveCamera::onEvent(Event& event)
    {
        if (!m_blockInput)
        {
            EventDispatcher dispatcher(event);
            dispatcher.dispatch<MouseMovedEvent>([this](MouseMovedEvent& event){ return onMouseMovedEvent(event); });
        }
    }

    Entity PerspectiveCamera::getPawn() const
    {
        return m_entity;
    }

    const glm::mat4& PerspectiveCamera::getViewProjection() const
    {
        return m_viewProjection;
    }

    bool PerspectiveCamera::isInputBlocked() const
    {
        return m_blockInput;
    }

    void PerspectiveCamera::updateViewProjection()
    {
		assert(m_entity);

		const auto& camera = m_entity.getComponent<CameraComponent>();
		const auto& transform = m_entity.getComponent<TransformComponent>();
		const auto& position = transform.getPosition();

        const auto right = glm::cross(camera.viewDirection, { 0.0f, 1.0f, 0.0f });
        const auto up = glm::cross(right, camera.viewDirection);

		const auto view = glm::inverse(transform.getWorldTransform());
        m_viewProjection = camera.projection * view;
    }

    bool PerspectiveCamera::onMouseMovedEvent(MouseMovedEvent& mouseEvent)
    {
		glm::vec2 newCursorPos{ mouseEvent.getX(), mouseEvent.getY() };
		if (m_oldCursorValid)
		{
			auto& camera = m_entity.getComponent<CameraComponent>();
			auto& transform = m_entity.getComponent<TransformComponent>();

			const auto delta = m_oldCursorPos - newCursorPos;
			const auto viewDirection = camera.viewDirection;
			const auto right = glm::cross(viewDirection, { 0.0f, 1.0f, 0.0f });

			auto quat1 = glm::angleAxis(delta.y / 200.0f, right);
			auto quat2 = glm::angleAxis(delta.x / 200.0f, glm::vec3{ 0.0, 1.0f, 0.0f });

			auto newRotation = quat1 * quat2 * transform.getRotation();
			transform.setRotation(newRotation);
		}
		else if (!m_blockInput)
		{
			m_oldCursorValid = true;
		}

        m_oldCursorPos = newCursorPos;
        updateViewProjection();

        return true;
    }

} // namespace bbzl
