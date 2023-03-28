#pragma once

#include "Butterfly/Core.h"
#include <glm/glm.hpp>

namespace butterfly
{
    class Camera;
    class Texture2D;

    class Shader;
    class PerspectiveCamera;

    namespace Renderer2D
    {
        void Init();
        void Destroy();

        void BeginScene(Camera* camera);
        void EndScene();
        void Flush();

        void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

        void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
        void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);

        void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture);
        void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture);

        void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color, const Ref<Texture2D>& texture);
        void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color, const Ref<Texture2D>& texture);

        Shader* Shader();
    } // namespace Renderer2D

} // namespace butterfly
