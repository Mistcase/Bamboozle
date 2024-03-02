#include "Bamboozle/bbzlpch.h"
#include "VulkanContext.h"
#include "VulkanShaders.h"

#include "vkDevice.h"
#include "VulkanShader.h"

#include "Bamboozle/Hash.h"
#include "Bamboozle/Log.h"
#include "Bamboozle/Renderer/Shader.h"

namespace
{
    std::vector<char> ReadFile(const std::string& filepath)
    {
        std::ifstream ifs(filepath, std::ios::ate | std::ios::binary);
        if (!ifs.is_open())
        {
            throw std::runtime_error("Failed to open file " + filepath);
        }

        std::vector<char> buffer(ifs.tellg());

        ifs.seekg(0);
        ifs.read(buffer.data(), buffer.size());
        ifs.close();

        return buffer;
    }

}

namespace bbzl
{
    VulkanShaders::VulkanShaders(vkDevice& device)
        : m_device(device)
    {
    }

    VulkanShaders::~VulkanShaders() = default;

    Shader* VulkanShaders::createFromFile(const std::filesystem::path& filepath)
    {
        // TODO: Error checking
        const auto code = ReadFile(filepath.generic_string());
        const auto name = filepath.stem().string();

        VulkanShader* shader = new VulkanShader(name);

        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = (const uint32_t*)code.data();

        const auto result = vkCreateShaderModule(m_device.getNativeDevice(), &createInfo, nullptr, shader->getNativeModulePtr()); 
        if (result != VK_SUCCESS)
        {
            // TODO: What shader?
            BBZL_CORE_ERROR("Cannot create shader");

            delete shader;
            return nullptr;
        }

        const auto key = hash(name);
        m_shaders[key].reset(shader);

        return shader;
    }

    Shader* VulkanShaders::get(uint32_t id)
    {
        auto it = m_shaders.find(id);
        if (it == m_shaders.end())
        {
            BBZL_CORE_INFO("Shader {0} is not found", id);
            return nullptr;
        }

        return it->second.get();
    }

    std::unique_ptr<Shader> VulkanShaders::extract(uint32_t id)
    {
        auto handle = m_shaders.extract(id);
        if (handle.empty())
            return nullptr;

        return std::unique_ptr<Shader>(handle.mapped().release());
    }

} // namespace bbzl