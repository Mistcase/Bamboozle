#include "Bubble/Renderer/Texture.h"
#include "bubblepch.h"
#include "Renderer2D.h"

#include "Bubble/Renderer/Camera.h"
#include "Bubble/Hash.h"
#include "Bubble/Renderer/RenderCommand.h"
#include "Bubble/Renderer/Shader.h"
#include "Bubble/Renderer/Shaders.h"
#include "Bubble/Renderer/Texture.h"
#include "Bubble/Renderer/VertexArray.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/ext/matrix_transform.hpp>

namespace
{
    struct _SceneData
    {
        _SceneData(std::unique_ptr<bubble::Shader>&& defaultShader, const bubble::Ref<bubble::VertexArray>& va)
            : shader(std::move(defaultShader))
            , vertexArray(va)
        {
        }

        bubble::Camera* camera;
        bubble::Ref<bubble::VertexArray> vertexArray;
        std::unique_ptr<bubble::Shader> shader = nullptr;
    };

    unsigned char SceneDataStorage[sizeof(_SceneData)];
    inline _SceneData* SceneData()
    {
        return reinterpret_cast<_SceneData*>(SceneDataStorage);
    }

    bubble::Ref<bubble::Texture2D> WhiteTexture;
    const uint32_t WhiteRGBA8 = 0xffffffff;

} // namespace

namespace bubble
{
    namespace Renderer2D
    {
        void Init()
        {
            // Temprorary object. Need it because of preprocessing and loading.
            auto shaders = Shaders::Create();
            shaders->createFromFile("renderer2D\\default_shader.glsl");

            auto defaultShader = shaders->extract("default_shader"_hash);
            BUBBLE_CORE_ASSERT(defaultShader != nullptr, "Default shader is not loaded");

            float vertices[] = {
                -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
                 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
                 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            };

            auto vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
            vertexBuffer->setLayout({
                    { bubble::ShaderDataType::Float3, "a_Position" },
                    { bubble::ShaderDataType::Float2, "a_TexCoords" }
            });

            uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
            auto indexBuffer = IndexBuffer::Create(indices, std::size(indices));

            auto vertexArray = VertexArray::Create();
            vertexArray->addVertexBuffer(vertexBuffer);
            vertexArray->setIndexBuffer(indexBuffer);

            WhiteTexture = Texture2D::Create(1, 1);
            WhiteTexture->setData(&WhiteRGBA8, sizeof(WhiteRGBA8));

            new (SceneDataStorage) _SceneData(std::move(defaultShader), vertexArray);
        }

        void Destroy()
        {
            SceneData()->~_SceneData();
        }

        void BeginScene(Camera* camera)
        {
            SceneData()->camera = camera;
            SceneData()->shader->bind();
        }

        void EndScene()
        {
        }

        void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
        {
            DrawQuad({ position.x, position.y, 0.0f }, size, color);
        }

        void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
        {
            const auto& viewProjection = SceneData()->camera->getViewProjection();
            const auto transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 0.0f });

            auto& shader = SceneData()->shader;
            static_cast<OpenGLShader*>(shader.get())->setUniformMat4("u_VP", viewProjection);
            static_cast<OpenGLShader*>(shader.get())->setUniformMat4("u_Transform", transform);
            static_cast<OpenGLShader*>(shader.get())->setUniform4f("u_Color", color);

            WhiteTexture->bind();

            SceneData()->vertexArray->bind();
            RenderCommand::DrawIndexed(SceneData()->vertexArray);
        }

        void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
        {
            DrawQuad({ position.x, position.y, 0.0f }, size, texture);
        }

        void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
        {
            const auto& viewProjection = SceneData()->camera->getViewProjection();
            const auto transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 0.0f });

            auto& shader = SceneData()->shader;
            static_cast<OpenGLShader*>(shader.get())->setUniformMat4("u_VP", viewProjection);
            static_cast<OpenGLShader*>(shader.get())->setUniformMat4("u_Transform", transform);
            static_cast<OpenGLShader*>(shader.get())->setUniform4f("u_Color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
            static_cast<OpenGLShader*>(shader.get())->setUniform1i("u_Texture", 0);

            texture->bind();

            SceneData()->vertexArray->bind();
            RenderCommand::DrawIndexed(SceneData()->vertexArray);
        }

    } // namespace Renderer2D

} // namespace bubble
