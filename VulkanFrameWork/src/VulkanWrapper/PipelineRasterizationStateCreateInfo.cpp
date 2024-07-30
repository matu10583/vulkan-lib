#include "VulkanWrapper/PipelineRasterizationStateCreateInfo.h"
namespace VulkanWrapper{
    PipelineRasterizationStateCreateInfo::PipelineRasterizationStateCreateInfo(VkFrontFace _frontFace)
        :VkPipelineRasterizationStateCreateInfo()
    {
        sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        depthClampEnable = VK_FALSE;
        rasterizerDiscardEnable = VK_FALSE;
        polygonMode = VK_POLYGON_MODE_FILL;
        lineWidth = 1.0f;
        cullMode = VK_CULL_MODE_BACK_BIT;
        frontFace = _frontFace;
        depthBiasEnable = VK_FALSE;
    }
    PipelineRasterizationStateCreateInfo::~PipelineRasterizationStateCreateInfo(){

        }
}
