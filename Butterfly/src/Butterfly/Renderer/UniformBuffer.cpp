#include "Butterfly/butterflypch.h"
#include "UniformBuffer.h"

#include "Butterfly/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace butterfly
{
	Ref<UniformBuffer> UniformBuffer::Create(size_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RenderAPI::API::None:
				assert(!"API is None");
				break;

        case RenderAPI::API::OpenGL:
            return std::make_shared<OpenGLUniformBuffer>(size);
            break;
		}

		assert(!"Unsupported renderer API");
		return nullptr;
	}

} // namespace
