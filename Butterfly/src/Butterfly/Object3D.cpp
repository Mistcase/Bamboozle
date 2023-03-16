#include "Object3D.h"

#include "Butterfly/Renderer/PerspectiveCamera.h"
#include "Butterfly/Renderer/VertexArray.h"
#include "Butterfly/Renderer/RenderCommand.h"

#include <glm/ext/matrix_transform.hpp>
#include <fstream>

namespace butterfly
{
	Object3D::Object3D(const std::filesystem::path& path)
	{
		struct Vertex
		{
			glm::vec4 position;
			glm::vec4 color;
			glm::vec3 normal;
			glm::vec2 uvCoords;
		};

		std::vector<Vertex> vertices;
		std::vector<IndexType> indices;

		std::ifstream stream(path.string());
		if (!stream.is_open())
		{
			assert(false);
		}

		size_t idxPosition = 0;
		size_t idxUVCoords = 0;
		size_t idxNormalCoords = 0;

		// Check if there is enough space in buffer
		auto receive_vertex = [&vertices](size_t idx) -> decltype(vertices[idx])
		{
			if (idx >= vertices.size())
				vertices.emplace_back();

			return vertices[idx];
		};

		std::string word;
		while (stream >> word)
		{
			if (word == "v")
			{
				// Vertex position
				auto& vertex = receive_vertex(idxPosition);
				auto& position = vertex.position;
				stream >> position.x;
				stream >> position.y;
				stream >> position.z;

				// Check if 4ht coordinate exists
				position.w = 1.0f; // 1.0f by default

				++idxPosition;
			}
			else if (word == "vt")
			{
				// Vertex texture coords
				// 3rd coordinate is not supported
				auto& vertex = receive_vertex(idxUVCoords);
				auto& uvCoords = vertex.uvCoords;

				stream >> uvCoords.x;
				stream >> uvCoords.y;
				++idxUVCoords;
			}
			else if (word == "vn")
			{
				// Vertex normal
				auto& vertex = receive_vertex(idxNormalCoords);
				auto& normal = vertex.normal;
				stream >> normal.x;
				stream >> normal.y;
				stream >> normal.z;

				// Normals can be non-normalized
				glm::normalize(normal);

				++idxNormalCoords;
			}
			else if (word == "vp")
			{
				// Unknown
				assert(false);
			}
			else if (word == "f")
			{
                loadFace(stream, indices);
			}
			else if (word == "g" || word == "o")
			{
				// group
			}
		}

		for (auto& vertex : vertices)
			vertex.color = { 0.8f, 0.0f, 0.0f, 1.0f };

		const auto vbSize = vertices.size() * sizeof(Vertex);
		m_vertexBuffer = VertexBuffer::Create(vbSize);
		m_vertexBuffer->setLayout({
				{ ShaderDataType::Float4, "Position", false },
				{ ShaderDataType::Float4, "Color", false },
				{ ShaderDataType::Float3, "Normal", false },
				{ ShaderDataType::Float2, "uvCoords", false },
			});
		m_vertexBuffer->setData(vertices.data(), vbSize);

		m_indexBuffer = IndexBuffer::Create(indices.size(), indices.data());
		m_vertexArray = VertexArray::Create();
		m_vertexArray->addVertexBuffer(m_vertexBuffer);
		m_vertexArray->setIndexBuffer(m_indexBuffer);
	}

	void Object3D::loadFace(std::ifstream& stream, std::vector<IndexType>& indices)
	{
		IndexType buffer[4];
		size_t count = 0;

		std::string word;
		auto processVertex = [&stream, &buffer, &count, &word]()
		{
			const auto pos = stream.tellg();
			stream >> word;
			if (!std::all_of(word.cbegin(), word.cend(), [](auto c){ return std::isdigit(c) || c == '/'; }))
			{
				stream.seekg(pos);
				return;
			}

			if (auto idxStart = word.find_first_of("/"); idxStart != std::string::npos)
			{
				const auto idxEnd = word.find_last_of("/");
				if (idxStart == idxEnd)
				{
					assert(!"Format is not supported");
				}
				else // Support for vertex//normal format
				{
					assert(idxStart + 1 == idxEnd);
					const auto idxPosition = std::stoi(word.substr(0, idxStart + 1));
					const auto idxNormal = std::stoi(word.substr(idxEnd + 1, word.size() - idxEnd - 1));
					assert(idxPosition == idxNormal);

					buffer[count++] = idxPosition - 1;
				}
			}
			else
			{
				buffer[count++] = std::stoi(word);
			}
		};

		for (size_t i = 0; i < 4; i++)
			processVertex();

		switch (count)
		{
		case 3:
			std::copy(std::cbegin(buffer), std::cbegin(buffer) + count, std::back_inserter(indices));
			break;

		case 4:
			indices.push_back(buffer[0]);
			indices.push_back(buffer[1]);
			indices.push_back(buffer[2]);
			indices.push_back(buffer[0]);
			indices.push_back(buffer[2]);
			indices.push_back(buffer[3]);
			break;

		default:
			assert(!"Format is not supported");

		}
	}

	void Object3D::setPosition(glm::vec3 position)
	{
		m_transform = glm::translate(glm::mat4(1.0f), position);
	}

	void Object3D::setRotation(float angle, glm::vec3 axis)
	{
		m_transform = glm::translate(glm::mat4(1.0f), m_position)
			* glm::rotate(glm::mat4(1.0f), angle, axis);
	}

	const glm::mat4& Object3D::getWorldTransform() const
	{
		return m_transform;
	}

	void Object3D::draw()
	{
		m_vertexArray->bind();
		RenderCommand::DrawIndexed(m_vertexArray);
	}
}
