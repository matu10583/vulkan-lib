#include "VulkanWrapper/PipelineColorBlendStateCreateInfo.h"
namespace VulkanWrapper{
    PipelineColorBlendStateCreateInfo::PipelineColorBlendStateCreateInfo(VkPipelineColorBlendAttachmentState const* _attachments, uint32_t _countAttachment)
        :VkPipelineColorBlendStateCreateInfo()
    {
        sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        pAttachments = _attachments;
        attachmentCount = _countAttachment;
        logicOpEnable = VK_FALSE;
    }
    PipelineColorBlendStateCreateInfo::~PipelineColorBlendStateCreateInfo(){

        }
}
