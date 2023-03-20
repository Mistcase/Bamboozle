#pragma once

#include "Butterfly/Core.h"
#include <glm/glm.hpp>
#include <filesystem>
#include <vector>

namespace butterfly
{
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;

	class PerspectiveCamera;

	class Object3D
	{
	public:
		Object3D(const std::filesystem::path& path);
		virtual ~Object3D() = default;

		void setPosition(glm::vec3 position);
		void setRotation(float angle, glm::vec3 axis);

		const glm::mat4& getWorldTransform() const;

		void draw();

	private:
		using IndexType = uint32_t;
		void loadFace(std::ifstream& stream, std::vector<IndexType>& indices);

	protected:
		Ref<VertexArray> m_vertexArray;
		Ref<VertexBuffer> m_vertexBuffer;
		Ref<IndexBuffer> m_indexBuffer;

		glm::mat4 m_transform;
		glm::vec3 m_position;
	};

}
