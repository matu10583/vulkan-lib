#include "VulkanWrapper/PipelineInputAssemblyStateCreateInfo.h"
namespace VulkanWrapper{
        PipelineInputAssemblyStateCreateInfo::~PipelineInputAssemblyStateCreateInfo(){

        }
        PipelineInputAssemblyStateCreateInfo::PipelineInputAssemblyStateCreateInfo(
            VkPrimitiveTopology _topology)
            :VkPipelineInputAssemblyStateCreateInfo()
                {
            sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
            topology = _topology;
            //あるindexを境に別のプリミティブにするようなことができるらしい
            primitiveRestartEnable = VK_FALSE;
        }
}
