#pragma once
#include "vulkan/vulkan.h"

namespace VulkanWrapper{
    class CommandPoolHandle;

class CommandBufferAllocateInfo
    :public VkCommandBufferAllocateInfo
{
public:
    CommandBufferAllocateInfo();
    CommandBufferAllocateInfo(
        CommandPoolHandle _commandPool,
        VkCommandBufferLevel _level,
        uint32_t _bufferCount
    );
private:

};
}
#include "VulkanWrapper/CommandBufferAllocateInfo.inl"