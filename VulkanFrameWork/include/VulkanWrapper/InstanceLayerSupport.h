#pragma once
#include "Lib/Container/Vector.h"
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
class InstanceLayerSupport
{
        public:
        InstanceLayerSupport();
        ~InstanceLayerSupport();

private:
    Lib::Container::Vector<VkLayerProperties> m_properties;
};
}
