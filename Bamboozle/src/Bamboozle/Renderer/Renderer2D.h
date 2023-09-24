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

        void DrawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 color);
        void DrawQuad(glm::vec3 position, glm::vec2 size, glm::vec4 color);

        void DrawQuad(glm::vec2 position, glm::vec2 size, Texture2D* texture);
        void DrawQuad(glm::vec3 position, glm::vec2 size, Texture2D* texture);

        void DrawQuad(glm::vec2 position, glm::vec2 size, glm::vec4 color, const Texture2D* texture);
        void DrawQuad(glm::vec3 position, glm::vec2 size, glm::vec4 color, const Texture2D* texture);

		void DrawQuad(glm::vec2 position, glm::vec2 size, float rotation, glm::vec4 color, const Texture2D* texture);
        void DrawQuad(glm::vec3 position, glm::vec2 size, float rotation, glm::vec4 color, const Texture2D* texture, glm::vec4 uv);

        Shader* Shader();

    } // namespace Renderer2D

} // namespace bbzl
