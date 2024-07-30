#include "VulkanWrapper/CommandPoolCreateInfo.h"

namespace VulkanWrapper{
    CommandPoolCreateInfo::CommandPoolCreateInfo()
        :VkCommandPoolCreateInfo()
    {
        sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    }

    CommandPoolCreateInfo::CommandPoolCreateInfo(uint32_t _queueFamilyIndex, VkCommandPoolCreateFlags _flags)
        :CommandPoolCreateInfo()
    {
        queueFamilyIndex = _queueFamilyIndex; 
        flags = _flags;
    }
}
