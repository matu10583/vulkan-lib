#pragma once
#include <vulkan/vulkan.h>

namespace VulkanWrapper{
	class PipelineLayoutHandle;
	class RenderPassHandle;
	class SubpassHandle;
class GraphicsPipelineCreateInfo
	:public VkGraphicsPipelineCreateInfo
{
public:
	GraphicsPipelineCreateInfo();
	
	GraphicsPipelineCreateInfo& VertexInputState(
		VkPipelineVertexInputStateCreateInfo const* _createInfo
	);
	GraphicsPipelineCreateInfo& InputAssemblyState(
		VkPipelineInputAssemblyStateCreateInfo const* _createInfo
	);
	GraphicsPipelineCreateInfo& ViewportState(
		VkPipelineViewportStateCreateInfo const* _createInfo
	);
	GraphicsPipelineCreateInfo& RasterizationStatetexInputState(
		VkPipelineRasterizationStateCreateInfo const* _createInfo
	);
	GraphicsPipelineCreateInfo& MultisampleState(
		VkPipelineMultisampleStateCreateInfo const* _createInfo
	);
	GraphicsPipelineCreateInfo& DepthStencilState(
		VkPipelineDepthStencilStateCreateInfo const* _createInfo
	);
	GraphicsPipelineCreateInfo& ColorBlendState(
		VkPipelineColorBlendStateCreateInfo const* _createInfo
	);
	GraphicsPipelineCreateInfo& DynamicState(
		VkPipelineDynamicStateCreateInfo const* _createInfo
	);

	GraphicsPipelineCreateInfo& PipelineLayout(
		PipelineLayoutHandle const _layout
	);
	GraphicsPipelineCreateInfo& ShaderStages(
		VkPipelineShaderStageCreateInfo const* _shaders,
		uint32_t _count
	);
	GraphicsPipelineCreateInfo& RenderPass(
		RenderPassHandle const _handle,
		uint32_t _subpass
	);

private:

};
}
#include "VulkanWrapper/GraphicsPipelineCreateInfo.inl"