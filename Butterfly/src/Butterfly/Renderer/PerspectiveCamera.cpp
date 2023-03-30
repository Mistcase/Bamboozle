#include "Butterfly/butterflypch.h"
#include "PerspectiveCamera.h"

#include "Butterfly/Log.h"
#include "Butterfly/Scene/Components.h"
#include "Butterfly/Transformable.h" // TODO: Rename as TransformComponent
#include "Butterfly/Events/Event.h"
#include "Butterfly/Events/MouseEvent.h"
#include "Butterfly/Input.h"
#include "Butterfly/KeyCodes.h"

namespace butterfly
{
	void PerspectiveCamera::possess(Entity entity)
	{
		m_entity = entity;
		updateViewProjection();
	}

    void PerspectiveCamera::blockInput(bool block)
    {
        m_blockInput = block;
    }

    void PerspectiveCamera::update(float dt)
    {
        const auto delta = dt;

        auto& camera = m_entity.getComponent<CameraComponent>();
		auto& transform = m_entity.getComponent<TransformComponent>();

        if (!m_blockInput)
        {
            if (Input::IsKeyPressed(BUTTERFLY_KEY_W))
            {
                transform.setPosition(transform.getPosition() + 0.25f * camera.viewDirection);
            }

            if (Input::IsKeyPressed(BUTTERFLY_KEY_S))
            {
                transform.setPosition(transform.getPosition() - 0.25f * camera.viewDirection);
            }

            if (Input::IsKeyPressed(BUTTERFLY_KEY_A))
            {
                const auto right = glm::cross(camera.viewDirection, glm::vec3(0.0f, 1.0f, 0.0f));
                transform.setPosition(transform.getPosition() - 0.25f * right);
            }

            if (Input::IsKeyPressed(BUTTERFLY_KEY_D))
            {
                const auto right = glm::cross(camera.viewDirection, glm::vec3(0.0f, 1.0f, 0.0f));
                transform.setPosition(transform.getPosition() + 0.25f * right);
            }
        }

        // TODO: FIXME, subscribe to transform changed!
        camera.viewDirection = glm::rotate(transform.getRotation(), { 0.0f, 0.0f, -1.0f });
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

        const auto view = glm::lookAt(position, position + camera.viewDirection, up);
        m_viewProjection = camera.projection * view;
    }

    bool PerspectiveCamera::onMouseMovedEvent(MouseMovedEvent& mouseEvent)
    {
        static bool firstTime = true;
        static glm::vec2 oldPos;

        if (!firstTime)
        {
            auto& camera = m_entity.getComponent<CameraComponent>();
            auto& transform = m_entity.getComponent<TransformComponent>();

            const auto delta = oldPos - glm::vec2{ mouseEvent.getX(), mouseEvent.getY() };
            const auto viewDirection = camera.viewDirection;
            const auto right = glm::cross(viewDirection, { 0.0f, 1.0f, 0.0f });

            auto quat1 = glm::angleAxis(delta.y / 200.0f, right);
            auto quat2 = glm::angleAxis(delta.x / 200.0f, glm::vec3{ 0.0, 1.0f, 0.0f });

            auto newRotation = quat1 * quat2 * transform.getRotation();
            transform.setRotation(newRotation);
        }

        firstTime = false;
        oldPos = { mouseEvent.getX(), mouseEvent.getY() };

        updateViewProjection();
        return true;
    }

} // namespace butterfly
