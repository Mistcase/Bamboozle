#include "bubblepch.h"
#include "Shader.h"

#include "Bubble/Log.h"
#include "Bubble/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include <glad/glad.h>

namespace bubble
{
    Shader* Shader::Create(const std::string& srcVertex, const std::string& srcFragment)
    {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL:
            return new OpenGLShader(srcVertex, srcFragment);

        default:
            break;
        }

        BUBBLE_CORE_ASSERT(false, "Unknown render API");
        return nullptr;
    }

} // namespace bubble
