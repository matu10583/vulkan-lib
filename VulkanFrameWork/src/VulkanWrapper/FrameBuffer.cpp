#include "VulkanWrapper/FrameBuffer.h"
#include "VulkanWrapper/Macro.h"
#include "VulkanWrapper/Device.h"

namespace VulkanWrapper{
    bool FrameBufferHandle::Init(
        DeviceHandle _dev,
        VkFramebufferCreateInfo const& _createInfo)
    {
        VEXCEPT(
            vkCreateFramebuffer(
                _dev.GetVulkanHandle(),
                &_createInfo, nullptr, &m_vkHandle
            )
        );
        return true;
    }
    void FrameBufferHandle::Destroy(DeviceHandle _dev)
    {
        vkDestroyFramebuffer(
            _dev.GetVulkanHandle(), m_vkHandle, nullptr
        );
    }
}
