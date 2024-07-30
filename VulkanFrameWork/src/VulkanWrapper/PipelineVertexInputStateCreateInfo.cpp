#include "VulkanWrapper/PipelineVertexInputStateCreateInfo.h"
namespace VulkanWrapper{
    PipelineVertexInputStateCreateInfo::PipelineVertexInputStateCreateInfo(
        VkVertexInputAttributeDescription const* _pAttrDescs, uint32_t _attrCount, VkVertexInputBindingDescription const* _pBindDescs, uint32_t _bindCount)
        :VkPipelineVertexInputStateCreateInfo()
    {
        sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        vertexAttributeDescriptionCount = _attrCount;
        pVertexAttributeDescriptions = _pAttrDescs;
        vertexBindingDescriptionCount = _bindCount;
        pVertexBindingDescriptions = _pBindDescs;
    }
    PipelineVertexInputStateCreateInfo::~PipelineVertexInputStateCreateInfo(){

        }
}
