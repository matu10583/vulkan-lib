#pragma once
#include <vulkan/vulkan.h>

namespace VulkanWrapper{

class CommandPoolCreateInfo
    :public VkCommandPoolCreateInfo
{
public:
    CommandPoolCreateInfo();
    CommandPoolCreateInfo(
        uint32_t _queueFamilyIndex,
        VkCommandPoolCreateFlags _flags
    );
private:

};
}
#include "VulkanWrapper/CommandPoolCreateInfo.inl"