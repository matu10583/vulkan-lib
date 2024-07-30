#include "VulkanWrapper/Semahore.h"
#include "VulkanWrapper/Macro.h"
#include "VulkanWrapper/Device.h"
namespace VulkanWrapper{
    bool SemaphoreHandle::Init(
        DeviceHandle _dev,
        VkSemaphoreCreateInfo const* _createInfo)
    {
        VEXCEPT(
            vkCreateSemaphore(
                _dev.GetVulkanHandle(),
                _createInfo, nullptr,
                &m_vkHandle
            )
        );
        return true;
    }
    void SemaphoreHandle::Destroy(DeviceHandle _dev)
    {
        vkDestroySemaphore(
            _dev.GetVulkanHandle(),
            m_vkHandle, nullptr
        );
    }
}
