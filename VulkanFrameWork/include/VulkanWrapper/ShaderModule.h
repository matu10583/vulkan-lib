#pragma once
#include "VulkanWrapper/VulkanHandleBase.h"
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
    class DeviceHandle;
    class ShaderModuleHandle
        :VulkanHandleBase<VkShaderModule> {
    public:
        ShaderModuleHandle();
        ~ShaderModuleHandle();
        bool Init(DeviceHandle _hDev, char const* fileName);
        void Destroy(DeviceHandle _handle);
    };
    
    class ShaderModule
{
        public:
        ShaderModule();
        ~ShaderModule();
};
}
