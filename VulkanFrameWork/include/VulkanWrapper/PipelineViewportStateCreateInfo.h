#pragma once
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
class PipelineViewportStateCreateInfo
    :public VkPipelineViewportStateCreateInfo
{
        public:
        PipelineViewportStateCreateInfo(
            VkViewport const* _viewPort,
            uint32_t _countViewPort,
            VkRect2D const* _scissor,
            uint32_t _countScissor
        );
        ~PipelineViewportStateCreateInfo();
};
}
