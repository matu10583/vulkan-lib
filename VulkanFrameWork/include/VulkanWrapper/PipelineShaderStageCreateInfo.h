#pragma once
#include <vulkan/vulkan.h>

namespace VulkanWrapper{
	class ShaderModuleHandle;
class PipelineShaderStageCreateInfo
	:public VkPipelineShaderStageCreateInfo
{
public:
	PipelineShaderStageCreateInfo();
	void SetShader(
		ShaderModuleHandle _module,
		char const* _pName,
		VkShaderStageFlagBits _stage
	);

private:

};
}
#include "VulkanWrapper/PipelineShaderStageCreateInfo.inl"