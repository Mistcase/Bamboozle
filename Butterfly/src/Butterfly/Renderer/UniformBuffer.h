#pragma once

#include "Butterfly/Core.h"

namespace butterfly
{
	class UniformBuffer
	{
	public:
		static Ref<UniformBuffer> Create(size_t size);

		virtual ~UniformBuffer() = default;

		virtual void bind(uint32_t bindPoint) const = 0;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void submit(const void* data, size_t size) const = 0;
	};

} // namespace
