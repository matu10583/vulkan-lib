#include "VulkanWrapper/CommandBufferBeginInfo.h"

namespace VulkanWrapper{
    CommandBufferBeginInfo::CommandBufferBeginInfo()
    {
        sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        flags = 0;
        pInheritanceInfo = nullptr;
    }
}
