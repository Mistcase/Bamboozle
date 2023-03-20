#include "Butterfly/butterflypch.h"
#include "Mesh.h"

#include "Butterfly/Renderer/VertexArray.h"
#include "Butterfly/Renderer/RenderCommand.h"

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
		const auto result = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());
		if (!result)
		{
			assert(false);
		}
		assert(shapes.size() == 1);

		std::vector<IndexType> indices;
		std::vector<Vertex> vertices;

		// Loop over faces(polygon)
		size_t index_offset = 0;
		auto& shape = shapes.front();

		for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++)
		{
			size_t fv = size_t(shape.mesh.num_face_vertices[f]);

			// Loop over vertices in the face.
			for (size_t v = 0; v < fv; v++)
			{
				// access to vertex
				tinyobj::index_t idx = shape.mesh.indices[index_offset + v];

				auto requiredSize = std::max(idx.vertex_index, std::max(idx.normal_index, idx.texcoord_index)) + 1;

				if (vertices.size() < requiredSize)
					vertices.resize(requiredSize);
				indices.push_back(idx.vertex_index);

				auto& position = vertices[idx.vertex_index].position;
				auto& normal = vertices[idx.normal_index].normal;
				auto& texCoords = vertices[idx.texcoord_index].uvCoords;

				position.x = attrib.vertices[3*size_t(idx.vertex_index)+0];
				position.y = attrib.vertices[3*size_t(idx.vertex_index)+1];
				position.z = attrib.vertices[3*size_t(idx.vertex_index)+2];
                position.w = 1.0f;

				// Check if `normal_index` is zero or positive. negative = no normal data
				if (idx.normal_index >= 0) {
					normal.x = attrib.normals[3*size_t(idx.normal_index)+0];
					normal.y = attrib.normals[3*size_t(idx.normal_index)+1];
					normal.z = attrib.normals[3*size_t(idx.normal_index)+2];
					normal = glm::normalize(normal);
				}

				// Check if `texcoord_index` is zero or positive. negative = no texcoord data
				if (idx.texcoord_index >= 0) {
					texCoords.x = attrib.texcoords[2*size_t(idx.texcoord_index)+0];
					texCoords.y = attrib.texcoords[2*size_t(idx.texcoord_index)+1];
				}
				// Optional: vertex colors
				// tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
				// tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
				// tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
			}
			index_offset += fv;

			// per-face material
			// shapes[s].mesh.material_ids[f];
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
