#pragma once

#include "Butterfly/Scene/Entity.h"

#include <glm/glm.hpp>

namespace butterfly
{
    class Event;
    class MouseMovedEvent;
    class KeyEvent;

    class PerspectiveCamera
    {
    public:
		void possess(Entity entity);
        void blockInput(bool block);

        void update(float dt);

        void onEvent(Event& event);

        Entity getPawn() const;
        glm::vec3 getViewDirection() const;
        const glm::mat4& getViewProjection() const;
        bool isInputBlocked() const;

    private:
        void updateViewProjection();

        bool onMouseMovedEvent(MouseMovedEvent& mouseEvent);
        bool onKeyEvent(KeyEvent& keyEvent);

    private:
        glm::mat4 m_viewProjection;
		glm::vec3 m_viewDirectionWorld;

	private:
		glm::vec2 m_oldCursorPos;

		Entity m_entity;
        bool m_blockInput = false;
		bool m_oldCursorValid = false;
    };

} // namespace butterfly
