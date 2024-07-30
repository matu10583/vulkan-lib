#pragma once
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
class PipelineMultisampleStateCreateInfo
    :public VkPipelineMultisampleStateCreateInfo
{
        public:
        PipelineMultisampleStateCreateInfo();
        ~PipelineMultisampleStateCreateInfo();
};
}
