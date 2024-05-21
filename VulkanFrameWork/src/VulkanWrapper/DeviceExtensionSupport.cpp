#include "VulkanWrapper/DeviceExtensionSupport.h"
#include "VulkanWrapper/Instance.h"
namespace VulkanWrapper{
        DeviceExtensionSupport::~DeviceExtensionSupport(){

        }
        DeviceExtensionSupport::DeviceExtensionSupport(PhysicalDeviceHandle _hPhysDev)
                {
            uint32_t extCount;
            vkEnumerateDeviceExtensionProperties(_hPhysDev.GetVulkanHandle(), nullptr, &extCount, nullptr);
            m_properties.Resize(extCount);
            vkEnumerateDeviceExtensionProperties(_hPhysDev.GetVulkanHandle(), nullptr, &extCount, m_properties.Data());
        }
}
