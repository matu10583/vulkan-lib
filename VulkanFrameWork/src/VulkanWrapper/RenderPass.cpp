#include "VulkanWrapper/RenderPass.h"
#include "VulkanWrapper/Macro.h"
#include "VulkanWrapper/Device.h"

namespace VulkanWrapper{
    bool RenderPassHandle::Init(VkRenderPassCreateInfo const& _createInfo, DeviceHandle _dev)
    {
        VEXCEPT(vkCreateRenderPass(
            _dev.GetVulkanHandle(),
            &_createInfo, nullptr,
            &m_vkHandle
        ));
        return true;
    }
    void RenderPassHandle::Destroy(DeviceHandle _dev)
    {
        vkDestroyRenderPass(
            _dev.GetVulkanHandle(),
            m_vkHandle, nullptr
        );
    }
}
