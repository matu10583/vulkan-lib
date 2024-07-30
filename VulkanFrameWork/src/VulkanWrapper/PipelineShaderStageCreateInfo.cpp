#include "VulkanWrapper/PipelineShaderStageCreateInfo.h"
#include "VulkanWrapper/ShaderModule.h"

namespace VulkanWrapper{
    PipelineShaderStageCreateInfo::PipelineShaderStageCreateInfo()
        :VkPipelineShaderStageCreateInfo()
    {
        sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        
    }
    void PipelineShaderStageCreateInfo::SetShader(ShaderModuleHandle _module, char const* _pName, VkShaderStageFlagBits _stage)
    {
        stage = _stage;
        module = _module.GetVulkanHandle();
        pName = _pName;
    }
}
