#pragma once
#include "Lib/Container/Array.h"
#include <vulkan/vulkan.h>
namespace VulkanWrapper{

class PipelineVertexInputStateCreateInfo
    :public VkPipelineVertexInputStateCreateInfo
{
        public:
        PipelineVertexInputStateCreateInfo(
            VkVertexInputAttributeDescription const* _pAttrDescs,
            uint32_t _attrCount,
            VkVertexInputBindingDescription const* _pBindDescs,
            uint32_t _bindCount
        );
        ~PipelineVertexInputStateCreateInfo();
};

}
