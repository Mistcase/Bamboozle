#include "Bamboozle/bbzlpch.h"
#include "PassTest.h"

#include "Bamboozle/Application.h"
#include "Bamboozle/ShaderPassTypes.h"
#include "Bamboozle/Renderer/Device.h"
#include "Bamboozle/Renderer/DeviceExecutionContext.h"
#include "Bamboozle/Renderer/DeviceExecutionContextFwd.h"
#include "Bamboozle/Renderer/DeviceFwd.h"
#include "Bamboozle/Renderer/PipelineState.h"
#include "Bamboozle/Renderer/VertexLayout.h"

namespace
{
    using ShaderData = std::vector<std::byte>;
    ShaderData LoadEntireFile(const std::filesystem::path& path)
    {
        std::ifstream ifs(path, std::ios::ate | std::ios::binary);
        ASSERT(ifs.is_open());

        ShaderData buffer(ifs.tellg());

        ifs.seekg(0);
        ifs.read((char*)buffer.data(), buffer.size());
        ifs.close();

        return buffer;
    }
} // namespace

namespace bbzl
{
    ShaderPassCommon::ShaderPassCommon()
    {
        m_vboLayout = {
            { VertexElementDataType::Float3, "position", false },
            { VertexElementDataType::Float3, "color", false },
        };

        // TODO: delete shaders???
        auto* vs = g_RenderDevice->createShader(Shader::Type::Vertex, LoadEntireFile(Application::GetInstance().getResourceDirectory() / "shaders/shader.vert.spv"));
        auto* fs = g_RenderDevice->createShader(Shader::Type::Pixel, LoadEntireFile(Application::GetInstance().getResourceDirectory() / "shaders/shader.frag.spv"));

        m_pso = g_RenderDevice->createPipelineStateObject();
        m_pso->passId = ShaderPassType::PASS_COMMON;
        m_pso->primTopologyType = PipelineState::PrimitiveTopologyType::Triangles;
        m_pso->vertexLayout = m_vboLayout;

        m_pso->shaderBundle[Shader::Type::Vertex] = vs;
        m_pso->shaderBundle[Shader::Type::Pixel] = fs;
    }

    ShaderPassCommon::~ShaderPassCommon()
    {
    }

    void ShaderPassCommon::prepare()
    {
        m_pso->validate();
        g_RenderContext->setPSO(*m_pso);
    }
}
