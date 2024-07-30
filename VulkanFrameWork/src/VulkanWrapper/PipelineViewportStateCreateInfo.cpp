#include "VulkanWrapper/PipelineViewportStateCreateInfo.h"
namespace VulkanWrapper{

    PipelineViewportStateCreateInfo::PipelineViewportStateCreateInfo(VkViewport const* _viewPort, uint32_t _countViewPort, VkRect2D const* _scissor, uint32_t _countScissor)
        :VkPipelineViewportStateCreateInfo()
    {
        sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportCount = _countViewPort;
        pViewports = _viewPort;
        scissorCount = _countScissor;
        pScissors = _scissor;
    }
    PipelineViewportStateCreateInfo::~PipelineViewportStateCreateInfo(){

        }
}
