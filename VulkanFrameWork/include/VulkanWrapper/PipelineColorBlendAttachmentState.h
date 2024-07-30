#pragma once
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
class PipelineColorBlendAttachmentState
    :public VkPipelineColorBlendAttachmentState
{
        public:
        PipelineColorBlendAttachmentState();
        ~PipelineColorBlendAttachmentState();
};
}
