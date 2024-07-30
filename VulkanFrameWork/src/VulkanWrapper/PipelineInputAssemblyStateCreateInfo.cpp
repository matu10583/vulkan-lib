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
            //����index�����ɕʂ̃v���~�e�B�u�ɂ���悤�Ȃ��Ƃ��ł���炵��
            primitiveRestartEnable = VK_FALSE;
        }
}
