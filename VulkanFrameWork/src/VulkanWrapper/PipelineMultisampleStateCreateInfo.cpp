#include "VulkanWrapper/PipelineMultisampleStateCreateInfo.h"
namespace VulkanWrapper{
        PipelineMultisampleStateCreateInfo::~PipelineMultisampleStateCreateInfo(){

        }
        PipelineMultisampleStateCreateInfo::PipelineMultisampleStateCreateInfo()
            :VkPipelineMultisampleStateCreateInfo()
                {
            sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
            sampleShadingEnable = VK_FALSE;
            rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        }
}
