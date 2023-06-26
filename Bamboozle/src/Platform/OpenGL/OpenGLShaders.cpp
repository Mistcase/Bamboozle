#include "OpenGLShaders.h"

#include "Bamboozle/Hash.h"
#include "Bamboozle/Log.h"
#include "Bamboozle/Renderer/Shader.h"
#include "Bamboozle/bbzl.h"
#include <fstream>

namespace bbzl
{
    OpenGLShaders::~OpenGLShaders() = default;

    Shader* OpenGLShaders::createFromFile(const std::filesystem::path& filepath)
    {
        const auto srcRaw = loadSource(filepath);
        const auto src = preprocess(srcRaw);

        const auto name = filepath.stem().string();
        auto instance = build(name, src);
        if (instance != nullptr)
        {
            const auto key = hash(name);
            m_shaders[key].reset(instance);

            BBZL_CORE_TRACE("Shader {0} loaded ({1})", name, filepath.string());
        }

        return instance;
    }

    Shader* OpenGLShaders::get(uint32_t id)
    {
        auto it = m_shaders.find(id);
        if (it == m_shaders.end())
        {
            BBZL_CORE_INFO("Shader {0} is not found", id);
            return nullptr;
        }

        return it->second.get();
    }

    std::unique_ptr<Shader> OpenGLShaders::extract(uint32_t id)
    {
        auto handle = m_shaders.extract(id);
        if (handle.empty())
            return nullptr;

        return std::unique_ptr<Shader>(handle.mapped().release());
    }

    std::string OpenGLShaders::loadSource(const std::filesystem::path& filepath) const
    {
        std::string source;

        const auto strPath = filepath.string();
        std::ifstream fs(strPath, std::ios::binary);
        if (!fs.is_open())
        {
            BBZL_CORE_ERROR("Cannot open shader source file {0}", strPath);
            return source;
        }

        // Allow to read empty files

        auto fsz = fs.tellg();
        fs.seekg(0, std::ios::end);
        fsz = fs.tellg() - fsz;
        fs.seekg(0, std::ios::beg);

        BBZL_CORE_TRACE("Shader file opened: size={0}, ({1})", fsz, strPath);

        source.resize(fsz);
        fs.read(source.data(), fsz);

        fs.close();

        return source;
    }

    OpenGLShaders::SourcePair OpenGLShaders::preprocess(const std::string& source) const
    {
        static constexpr char labels[] = { '@' };
        static constexpr char delimiters[] = { ' ', '\r', '\n' };

        std::string srcVertex;
        std::string srcFragment;

        const auto srcSize = source.size();
        srcVertex.reserve(srcSize);
        srcFragment.reserve(srcSize);

        // Now it just handle labels: @VertexShader; @FragmentShader
        std::string* srcCurrent = &srcVertex;
        std::string label;
        bool readLabel = false;

        auto activateLabel = [&readLabel]() { readLabel = true; };
        auto handleLabel = [&]() {
            if (!readLabel)
                return;

            switch (hash(label.c_str()))
            {
            case "VertexShader"_hash:
                srcCurrent = &srcVertex;
                break;

            case "FragmentShader"_hash:
                srcCurrent = &srcFragment;
                break;

            default:
                break;
            }

            label.clear();
            readLabel = false;
        };

        for (size_t i = 0; i < srcSize; i++)
        {
            const auto s = source[i];
            const auto isDelimiter = std::find(std::cbegin(delimiters), std::cend(delimiters), s) != std::cend(delimiters);
            const auto isLabel = std::find(std::cbegin(labels), std::cend(labels), s) != std::cend(labels);

            if (isLabel)
            {
                activateLabel();
                continue;
            }

            if (isDelimiter)
                handleLabel();

            if (readLabel)
                label.push_back(s);
            else
                srcCurrent->push_back(s);
        }

        return { srcVertex, srcFragment };
    }

    OpenGLShader* OpenGLShaders::build(const std::string& name, const SourcePair& sources)
    {
        auto instance = new OpenGLShader(name, sources.first, sources.second);
        if (!instance->m_isAssembled)
        {
            delete instance;
            return nullptr;
        }

        return instance;
    }

} // namespace bbzl
