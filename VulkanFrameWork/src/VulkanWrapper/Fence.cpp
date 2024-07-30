#include "VulkanWrapper/Fence.h"
#include "VulkanWrapper/Device.h"
#include "VulkanWrapper/Macro.h"
namespace VulkanWrapper{
    bool FenceHandle::Init(DeviceHandle _device, VkFenceCreateInfo const* _pCreateInfo)
    {
        VEXCEPT(
            vkCreateFence(
                _device.GetVulkanHandle(),
                _pCreateInfo, nullptr,
                &m_vkHandle
            )
        );
        return true;
    }
    void FenceHandle::Destroy(DeviceHandle _dev)
    {
        vkDestroyFence(
            _dev.GetVulkanHandle(),
            m_vkHandle, nullptr
        );
    }

}
