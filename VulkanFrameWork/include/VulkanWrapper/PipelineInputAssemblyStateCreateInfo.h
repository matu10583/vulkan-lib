#pragma once
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
class PipelineInputAssemblyStateCreateInfo
    :public VkPipelineInputAssemblyStateCreateInfo
{
        public:
        PipelineInputAssemblyStateCreateInfo(
        VkPrimitiveTopology _topology);
        ~PipelineInputAssemblyStateCreateInfo();
};
}
