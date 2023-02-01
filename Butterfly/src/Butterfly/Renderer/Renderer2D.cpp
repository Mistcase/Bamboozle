#include "Butterfly/butterflypch.h"
#include "Renderer2D.h"

#include "Butterfly/Application.h"
#include "Butterfly/Renderer/Camera.h"
#include "Butterfly/Hash.h"
#include "Butterfly/Renderer/RenderCommand.h"
#include "Butterfly/Renderer/Shader.h"
#include "Butterfly/Renderer/Shaders.h"
#include "Butterfly/Renderer/Texture.h"
#include "Butterfly/Renderer/VertexArray.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/ext/matrix_transform.hpp>

namespace butterfly
{
    namespace
    {
        const glm::vec4 QuadPositions[] = {
            { -0.5f,  0.5f, 0.0f, 1.0f },
            {  0.5f,  0.5f, 0.0f, 1.0f },
            {  0.5f, -0.5f, 0.0f, 1.0f },
            { -0.5f, -0.5f, 0.0f, 1.0f }
        };

        const BufferLayout VertexDesc {
            { ShaderDataType::Float4, "a_Position" },
            { ShaderDataType::Float4, "a_Color" },
            { ShaderDataType::Float2, "a_TexCoords" },
            { ShaderDataType::Float, "a_TexIndex" },
        };

        struct _SceneData
        {
            butterfly::Ref<butterfly::Texture2D> WhiteTexture;
            static const uint32_t WhiteRGBA8 = 0xffffffff;
            static const size_t MaxQuadCount = 10'000;
            static const size_t MaxVertexCount = MaxQuadCount * 4;
            static const size_t MaxIndexCount = MaxQuadCount * 6;

            std::array<Ref<Texture2D>, 16> textureSlots;
            uint32_t textureIndex = 2; // 0 - used for Texture creation; 1 - default white texture.

            uint8_t storage[MaxVertexCount * sizeof(VertexDesc)];
            uint8_t* quadVertexBufferBase = storage;
            uint8_t* quadVertexBufferPtr = quadVertexBufferBase;
            size_t quadCount = 0;

            butterfly::Camera* camera = nullptr;
            butterfly::Ref<butterfly::VertexArray> vertexArray;
            std::unique_ptr<butterfly::Shader> shader = nullptr;

            [[maybe_unused]] uint32_t debugDrawCalls = 0;
        };

        unsigned char SceneDataStorage[sizeof(_SceneData)];
        inline _SceneData* SceneData(){ return reinterpret_cast<_SceneData*>(SceneDataStorage); }

    } // namespace

    namespace Renderer2D
    {
        void Init()
        {
            // Configure fields
            new (SceneDataStorage) _SceneData();
            BUTTERFLY_CORE_ASSERT(SceneData()->textureSlots.size() > 2, "Cannot render user provided textures");

            // Temprorary object. Need it because of preprocessing and loading.
			auto res = Application::GetInstance().getResourcesDirectory();
            auto shaders = Shaders::Create();
			shaders->createFromFile(res.concat("default_shader.glsl"));

            SceneData()->shader = shaders->extract("default_shader"_hash);
            BUTTERFLY_CORE_ASSERT(SceneData()->shader != nullptr, "Default shader is not loaded");

            auto vertexArray = VertexArray::Create();

            auto vertexBuffer = VertexBuffer::Create(_SceneData::MaxVertexCount * VertexDesc.getStride());
            vertexBuffer->setLayout(VertexDesc);

            auto indexBuffer = IndexBuffer::Create(_SceneData::MaxIndexCount);
            auto indexBufferData = new uint32_t[_SceneData::MaxIndexCount];
            for (uint32_t i = 0, idxBaseStart = 0; i < _SceneData::MaxIndexCount; i += 6, idxBaseStart += 4)
            {
                indexBufferData[i + 0] = idxBaseStart + 0;
                indexBufferData[i + 1] = idxBaseStart + 1;
                indexBufferData[i + 2] = idxBaseStart + 2;
                indexBufferData[i + 3] = idxBaseStart + 2;
                indexBufferData[i + 4] = idxBaseStart + 3;
                indexBufferData[i + 5] = idxBaseStart + 0;
            }
            indexBuffer->setData(indexBufferData, _SceneData::MaxIndexCount);
            delete[] indexBufferData;

            vertexArray->addVertexBuffer(vertexBuffer);
            vertexArray->setIndexBuffer(indexBuffer);

            SceneData()->vertexArray = std::move(vertexArray);

            auto v = _SceneData::WhiteRGBA8;
            SceneData()->WhiteTexture = Texture2D::Create(1, 1);
            SceneData()->WhiteTexture->setData(&v, sizeof(uint32_t));
            SceneData()->textureSlots[1] = SceneData()->WhiteTexture;

            const auto size = static_cast<int>(SceneData()->textureSlots.size());
            auto samplers = static_cast<int*>(alloca(sizeof(int32_t) * size));
            for (int i = 0; i < size; i++)
                samplers[i] = i;

            SceneData()->shader->bind();
            static_cast<OpenGLShader*>(SceneData()->shader.get())->setUniformIntArray("u_Textures", samplers, size);
        }

        void Destroy()
        {
            SceneData()->~_SceneData();
        }

        void BeginScene(Camera* camera)
        {
            SceneData()->camera = camera;
            SceneData()->shader->bind();

            const auto& viewProjection = SceneData()->camera->getViewProjection();
            static_cast<OpenGLShader*>(SceneData()->shader.get())->setUniformMat4("u_VP", viewProjection);
        }

        void EndScene()
        {
            Flush();

            // BUTTERFLY_CORE_INFO("Draw calls: {0}", SceneData()->debugDrawCalls);

#if defined(BUTTERFLY_DEBUG)
            SceneData()->debugDrawCalls = 0;
#endif
        }

        void Flush()
        {
            SceneData()->vertexArray->bind();

            // Does shader always stay bound?
            for (uint32_t i = 1, idxEnd = SceneData()->textureIndex; i < idxEnd; i++)
                SceneData()->textureSlots[i]->bind(i);

            auto& vertexBuffer = SceneData()->vertexArray->getVertexBuffers().front();
            const auto dataSize = SceneData()->quadVertexBufferPtr - SceneData()->quadVertexBufferBase;
            vertexBuffer->setData(SceneData()->quadVertexBufferBase, dataSize);

            RenderCommand::DrawIndexed(SceneData()->vertexArray, SceneData()->quadCount * 6);

            SceneData()->quadVertexBufferPtr = SceneData()->quadVertexBufferBase;
            SceneData()->quadCount = 0;
            SceneData()->textureIndex = 2;

#if defined(BUTTERFLY_DEBUG)
            SceneData()->debugDrawCalls++;
#endif
        }

        void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
        {
            DrawQuad({ position.x, position.y, 0.0f }, size, 0.0f, color, SceneData()->WhiteTexture);
        }

        void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
        {
            DrawQuad(position, size, 0.0f, color, SceneData()->WhiteTexture);
        }

        void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
        {
            DrawQuad({ position.x, position.y, 0.0f }, size, 0.0f, { 1.0f, 1.0f, 1.0f, 1.0f }, texture);
        }

        void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
        {
            DrawQuad(position, size, 0.0f, { 1.0f, 1.0f, 1.0f, 1.0f }, texture);
        }

        void DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color, const Ref<Texture2D>& texture)
        {
            DrawQuad({ position.x, position.y, 0.0f }, size, rotation, color, texture);
        }

        void DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color, const Ref<Texture2D>& texture)
        {
            BUTTERFLY_CORE_ASSERT(texture != nullptr, "Texture is nullptr");

            if (SceneData()->quadCount >= SceneData()->MaxQuadCount)
                Flush();

            float textureSlot = 1.0f; // Because int's cannot be interpolated (compile error)
            if (texture != SceneData()->WhiteTexture)
            {
                for (uint32_t i = 1, idxEnd = SceneData()->textureIndex; i < idxEnd; i++)
                {
                    if (*SceneData()->textureSlots[i] == *texture)
                    {
                        textureSlot = static_cast<float>(i);
                        break;
                    }
                }

                if (textureSlot == 1.0f)
                {
                    if (SceneData()->textureIndex >= SceneData()->textureSlots.size())
                        Flush();

                    SceneData()->textureSlots[SceneData()->textureIndex] = texture;
                    textureSlot = static_cast<float>(SceneData()->textureIndex);

                    SceneData()->textureIndex++;
                }
            }

            // Does not support texture atlases yet
            const glm::vec2 texCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
            const auto transform = glm::translate(glm::mat4(1.0f), position)
                * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
                * glm::scale(glm::mat4(1.0f), { size.x, size.y, 0.0f });

            for (size_t i = 0; i < 4; i++)
            {
                const auto position = transform * QuadPositions[i];
                memcpy(SceneData()->quadVertexBufferPtr, &position, sizeof(position));
                SceneData()->quadVertexBufferPtr += sizeof(position);

                memcpy(SceneData()->quadVertexBufferPtr, &color, sizeof(color));
                SceneData()->quadVertexBufferPtr += sizeof(color);

                memcpy(SceneData()->quadVertexBufferPtr, &texCoords[i], sizeof(glm::vec2));
                SceneData()->quadVertexBufferPtr += sizeof(glm::vec2);

                memcpy(SceneData()->quadVertexBufferPtr, &textureSlot, sizeof(textureSlot));
                SceneData()->quadVertexBufferPtr += sizeof(textureSlot);
            }

            SceneData()->quadCount++;
        }

    } // namespace Renderer2D

} // namespace butterfly
