#include "VulkanWrapper/ShaderModule.h"
#include "VulkanWrapper/Device.h"
#include "Lib/Utility/File.h"
#include "VulkanWrapper/Macro.h"
namespace VulkanWrapper{
        ShaderModule::~ShaderModule(){

        }
        ShaderModule::ShaderModule()
                {

        }
        ShaderModuleHandle::ShaderModuleHandle()
        {
        }
        ShaderModuleHandle::~ShaderModuleHandle()
        {
        }
        bool ShaderModuleHandle::Init(DeviceHandle _hDev, char const* _fileName)
        {
            Lib::Utility::File file{};
            if (!file.ReadFile(_fileName)) {
                throw std::runtime_error("シェーダーファイルが存在しません");
                return false;
            }
            VkShaderModuleCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
            createInfo.codeSize = file.GetSize();
            createInfo.pCode = reinterpret_cast<uint32_t* const>(file.Data());
            VEXCEPT(
                vkCreateShaderModule(
                    _hDev.GetVulkanHandle(), &createInfo, nullptr, &m_vkHandle
                )
            );

            return true;
        }
        void ShaderModuleHandle::Destroy(DeviceHandle _handle)
        {
            vkDestroyShaderModule(_handle.GetVulkanHandle(), m_vkHandle, nullptr);
        }
}
