#pragma once
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
class PipelineRasterizationStateCreateInfo
    :public VkPipelineRasterizationStateCreateInfo
{
        public:
        PipelineRasterizationStateCreateInfo(
            VkFrontFace _frontFace
        );
        ~PipelineRasterizationStateCreateInfo();
};
}
