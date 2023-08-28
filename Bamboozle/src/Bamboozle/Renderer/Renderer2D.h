#pragma once

#include "Bamboozle/Core.h"
#include <glm/glm.hpp>

namespace bbzl
{
    class OrthographicCamera;
    class Texture2D;

    class Shader;
    class PerspectiveCamera;

    namespace Renderer2D
    {
        void Init();
        void Destroy();

        void BeginScene(OrthographicCamera* camera);
        void EndScene();
        void Flush();

        void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

        void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Texture2D* texture);
        void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Texture2D* texture);

        void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const Texture2D* texture);
        void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Texture2D* texture);

        void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color, const Texture2D* texture);
        void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color, const Texture2D* texture);

        Shader* Shader();

    } // namespace Renderer2D

} // namespace bbzl
