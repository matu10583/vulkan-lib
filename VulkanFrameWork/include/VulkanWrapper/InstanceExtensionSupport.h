#pragma once

#include "Lib/Container/Vector.h"
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
class InstanceExtensionSupport
{
        public:
        InstanceExtensionSupport();
        ~InstanceExtensionSupport();
        bool AreSupported(char const** _pStrs, uint32_t _size)const;
private:
    Lib::Container::Vector<VkExtensionProperties> m_properties;
};
}
