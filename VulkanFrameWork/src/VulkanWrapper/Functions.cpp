#include "VulkanWrapper/Functions.h"
#include "VulkanWrapper/Device.h"
#include "VulkanWrapper/CommandBufferAllocateInfo.h"
#include "VulkanWrapper/CommandBuffer.h"
#include "VulkanWrapper/Macro.h"

namespace VulkanWrapper{
    bool AllocateCommandBuffer(DeviceHandle _device, CommandBufferAllocateInfo const& _createInfo, CommandBufferHandle* _outHandles)
    {
        VEXCEPT(
            vkAllocateCommandBuffers(
                _device.GetVulkanHandle(),
                &_createInfo,
                reinterpret_cast<VkCommandBuffer*>(_outHandles)
            )
        );
        return true;
    }
}
