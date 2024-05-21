#pragma once
#include "Lib/Container/Vector.h"
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
    class PhysicalDeviceHandle;
class DeviceExtensionSupport
{
        public:
        DeviceExtensionSupport(PhysicalDeviceHandle _hPhysDev);
        ~DeviceExtensionSupport();
private:
    Lib::Container::Vector<VkExtensionProperties> m_properties;
};
}
