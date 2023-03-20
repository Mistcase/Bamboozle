#pragma once

#include "Butterfly/Core.h"

#include <filesystem>
#include <glm/glm.hpp>
#include <vector>

namespace butterfly
{
    class VertexArray;
	class VertexBuffer;
	class IndexBuffer;

    class Mesh
    {
    public:
        using IndexType = uint32_t;
        struct Vertex
        {
            glm::vec4 position;
            glm::vec4 color;
            glm::vec3 normal;
            glm::vec2 uvCoords;
        };
        using VertexContainer = std::vector<Vertex>;
        using IndexContainer = std::vector<IndexType>;

    public:
        static Ref<Mesh> Create(const std::filesystem::path& path);
        const VertexContainer& getRawData() const;

        void draw() const;

    private:
        Mesh(VertexContainer&& vertices, const IndexContainer& indices);

    private:
        Ref<VertexArray> m_vertexArray;
		Ref<VertexBuffer> m_vertexBuffer;
		Ref<IndexBuffer> m_indexBuffer;

        VertexContainer m_vertices;
    };

} // namepsace butterfly
