#pragma once

namespace bbzl
{
    enum class VertexElementDataType : uint8_t
    {
        None = 0,
        Float,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Int,
        Int2,
        Int3,
        Int4,
        Bool
    };

    struct VertexBufferElement
    {
        std::string name;
        size_t size = 0;
        uint32_t offset = 0;
        VertexElementDataType type;
        bool normalized;

        VertexBufferElement(VertexElementDataType _type, const std::string& _name, bool normalized = false);
        size_t getComponentCount() const;
    };

    class VertexLayout
    {
    public:
        using Elements = std::vector<VertexBufferElement>;

    public:
        VertexLayout() = default;
        VertexLayout(std::initializer_list<VertexBufferElement> elements);

        uint32_t getStride() const
        {
            return m_stride;
        }
        const Elements& getElements() const
        {
            return m_elements;
        }

        Elements::iterator begin()
        {
            return m_elements.begin();
        }
        Elements::iterator end()
        {
            return m_elements.end();
        }
        Elements::const_iterator begin() const
        {
            return m_elements.begin();
        }
        Elements::const_iterator end() const
        {
            return m_elements.end();
        }

    private:
        void calculateOffsetsAndStride();

    private:
        Elements m_elements;
        uint32_t m_stride;
    };

}