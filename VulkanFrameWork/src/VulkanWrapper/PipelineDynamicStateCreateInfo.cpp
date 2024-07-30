#include "VulkanWrapper/PipelineDynamicStateCreateInfo.h"
namespace VulkanWrapper{
    PipelineDynamicStateCreateInfo::PipelineDynamicStateCreateInfo(VkDynamicState const* _pDss, uint32_t _dsCount)
        :VkPipelineDynamicStateCreateInfo()
    {
        sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamicStateCount = _dsCount;
        pDynamicStates = _pDss;
    }
    PipelineDynamicStateCreateInfo::~PipelineDynamicStateCreateInfo(){

        }
}
