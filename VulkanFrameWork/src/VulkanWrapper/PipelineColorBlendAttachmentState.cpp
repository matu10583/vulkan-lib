#include "VulkanWrapper/PipelineColorBlendAttachmentState.h"
namespace VulkanWrapper{
        PipelineColorBlendAttachmentState::~PipelineColorBlendAttachmentState(){

        }
        PipelineColorBlendAttachmentState::PipelineColorBlendAttachmentState()
            :VkPipelineColorBlendAttachmentState()
                {
            colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
            blendEnable = VK_FALSE;
        }
}
