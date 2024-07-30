#pragma once
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
class PipelineDynamicStateCreateInfo
    :public VkPipelineDynamicStateCreateInfo
{
        public:
        PipelineDynamicStateCreateInfo(
            VkDynamicState const* _pDss,
            uint32_t _dsCount
        );
        ~PipelineDynamicStateCreateInfo();
};
}
