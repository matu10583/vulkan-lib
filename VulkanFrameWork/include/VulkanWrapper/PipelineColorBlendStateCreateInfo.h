#pragma once
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
class PipelineColorBlendStateCreateInfo
    :public VkPipelineColorBlendStateCreateInfo
{
        public:
        PipelineColorBlendStateCreateInfo(
            VkPipelineColorBlendAttachmentState const* _attachments,
            uint32_t _countAttachment
        );
        ~PipelineColorBlendStateCreateInfo();
};
}
