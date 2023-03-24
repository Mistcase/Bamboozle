#include "Mesh.h"

#include "Butterfly/Renderer/RenderCommand.h"
#include "Butterfly/Renderer/VertexArray.h"
#include "Butterfly/butterflypch.h"
#include <fstream>
#include <vector>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

namespace butterfly
{
    Ref<Mesh> Mesh::Create(const std::filesystem::path& path)
    {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;

        std::string warn;
        std::string err;
        const auto result = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.generic_string().c_str());
        if (!result)
        {
            assert(false);
        }

        size_t indexCount = 0;
        for (const auto& shape : shapes)
        {
            for (auto numFaceVertices : shape.mesh.num_face_vertices)
                indexCount += numFaceVertices;
        }

        std::vector<Vertex> vertices;
        std::vector<IndexType> indices;
        vertices.reserve(indexCount);
        indices.reserve(indexCount);

        size_t idxTotal = 0;
        for (const auto& shape : shapes)
        {
            size_t indexOffset = 0;
            const auto& mesh = shape.mesh;

            for (auto numFaceVertices : mesh.num_face_vertices)
            {
                for (size_t i = 0; i < size_t(numFaceVertices); i++)
                {
                    // TODO: Dont create duplicate vertices if it is possible
                    vertices.emplace_back();
                    auto& last = vertices.back();
                    auto& position = last.position;
                    auto& normal = last.normal;
                    auto& texCoords = last.uvCoords;

                    tinyobj::index_t idx = mesh.indices[indexOffset + i];
                    indices.push_back(idxTotal + i);

                    position.x = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
                    position.y = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
                    position.z = attrib.vertices[3 * size_t(idx.vertex_index) + 2];
                    position.w = 1.0f;

                    if (idx.normal_index >= 0)
                    {
                        normal.x = attrib.normals[3 * size_t(idx.normal_index) + 0];
                        normal.y = attrib.normals[3 * size_t(idx.normal_index) + 1];
                        normal.z = attrib.normals[3 * size_t(idx.normal_index) + 2];
                        normal = glm::normalize(normal);
                    }

                    if (idx.texcoord_index >= 0)
                    {
                        texCoords.x = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
                        texCoords.y = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
                    }
                }

                indexOffset += numFaceVertices;
                idxTotal += numFaceVertices;
            }
        }

        auto instance = new Mesh(std::move(vertices), indices);
        return Ref<Mesh>(instance);
    }

    Mesh::Mesh(VertexContainer&& vertices, const IndexContainer& indices)
        : m_vertices(std::move(vertices))
    {
        for (auto& vertex : m_vertices)
            vertex.color = { 0.8f, 0.0f, 0.0f, 1.0f };

        const auto vbSize = m_vertices.size() * sizeof(Vertex);
        m_vertexBuffer = VertexBuffer::Create(vbSize);
        m_vertexBuffer->setLayout({
            { ShaderDataType::Float4, "Position", false },
            { ShaderDataType::Float4, "Color", false },
            { ShaderDataType::Float3, "Normal", false },
            { ShaderDataType::Float2, "uvCoords", false },
        });
        m_vertexBuffer->setData(m_vertices.data(), vbSize);

        m_indexBuffer = IndexBuffer::Create(indices.size(), indices.data());
        m_vertexArray = VertexArray::Create();
        m_vertexArray->addVertexBuffer(m_vertexBuffer);
        m_vertexArray->setIndexBuffer(m_indexBuffer);
    }

    const Mesh::VertexContainer& Mesh::getRawData() const
    {
        return m_vertices;
    }

    void Mesh::draw() const
    {
        m_vertexArray->bind();
        RenderCommand::DrawIndexed(m_vertexArray);
    }

} // namespace butterfly
