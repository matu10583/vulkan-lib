#pragma once
#include "VulkanWrapper/VulkanHandleBase.h"
#include "VulkanWrapper/ExtFunctionDispatchable.h"
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
    class InstanceHandle;
class DebugMessengerHandle
:
public VulkanWrapper::VulkanHandleBase<VkDebugUtilsMessengerEXT>,
public VulkanWrapper::ExtFunctionDispatchable
{
public:
        DebugMessengerHandle();
        ~DebugMessengerHandle();
        bool Init(
            InstanceHandle handle,
            VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo
        );
        void Destroy(InstanceHandle handle);
};
}
