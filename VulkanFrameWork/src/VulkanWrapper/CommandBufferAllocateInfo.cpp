#include "VulkanWrapper/CommandBufferAllocateInfo.h"
#include "VulkanWrapper/CommandPool.h"

namespace VulkanWrapper{
    CommandBufferAllocateInfo::CommandBufferAllocateInfo()
        :VkCommandBufferAllocateInfo()
    {
        sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    }
    CommandBufferAllocateInfo::CommandBufferAllocateInfo(
        CommandPoolHandle _commandPool,
        VkCommandBufferLevel _level, 
        uint32_t _bufferCount)
        :CommandBufferAllocateInfo()
    {
        commandPool = _commandPool.GetVulkanHandle();
        level = _level;
        commandBufferCount = _bufferCount;

    }
}
