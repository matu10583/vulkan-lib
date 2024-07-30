#include "VulkanWrapper/CommandPool.h"
#include "VulkanWrapper/Macro.h"
#include "VulkanWrapper/Device.h"
#include "VulkanWrapper/CommandBufferAllocateInfo.h"
#include "VulkanWrapper/CommandBuffer.h"
#include "VulkanWrapper/Functions.h"

namespace VulkanWrapper{

    bool CommandPoolHandle::Init(DeviceHandle _device, VkCommandPoolCreateInfo const& _createInfo)
    {
        VEXCEPT(
            vkCreateCommandPool(
                _device.GetVulkanHandle(),
                &_createInfo, nullptr, &m_vkHandle
            )
        );
        return true;
    }
    void CommandPoolHandle::Destroy(DeviceHandle _device)
    {
        vkDestroyCommandPool(
            _device.GetVulkanHandle(),
            m_vkHandle, nullptr
        );
    }

}
