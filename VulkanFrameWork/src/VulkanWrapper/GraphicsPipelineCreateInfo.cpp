#include "VulkanWrapper/GraphicsPipelineCreateInfo.h"
#include "VulkanWrapper/RenderPass.h"
#include "VulkanWrapper/PipelineLayout.h"

namespace VulkanWrapper{
    GraphicsPipelineCreateInfo::GraphicsPipelineCreateInfo()
        :VkGraphicsPipelineCreateInfo()
    {
        sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        basePipelineHandle = VK_NULL_HANDLE;
        basePipelineIndex = -1;
        pDepthStencilState = nullptr;
    }
    GraphicsPipelineCreateInfo& GraphicsPipelineCreateInfo::VertexInputState(VkPipelineVertexInputStateCreateInfo const* _createInfo)
    {
        pVertexInputState = _createInfo;
        return *this;
        // TODO: return ステートメントをここに挿入します
    }
    GraphicsPipelineCreateInfo& GraphicsPipelineCreateInfo::InputAssemblyState(VkPipelineInputAssemblyStateCreateInfo const* _createInfo)
    {
        pInputAssemblyState = _createInfo;
        return *this;
        // TODO: return ステートメントをここに挿入します
    }
    GraphicsPipelineCreateInfo& GraphicsPipelineCreateInfo::ViewportState(VkPipelineViewportStateCreateInfo const* _createInfo)
    {
        pViewportState = _createInfo;
        return *this;
        // TODO: return ステートメントをここに挿入します
    }
    GraphicsPipelineCreateInfo& GraphicsPipelineCreateInfo::RasterizationStatetexInputState(VkPipelineRasterizationStateCreateInfo const* _createInfo)
    {
        pRasterizationState = _createInfo;
        return *this;
        // TODO: return ステートメントをここに挿入します
    }
    GraphicsPipelineCreateInfo& GraphicsPipelineCreateInfo::MultisampleState(VkPipelineMultisampleStateCreateInfo const* _createInfo)
    {
        pMultisampleState = _createInfo;
        return *this;
        // TODO: return ステートメントをここに挿入します
    }
    GraphicsPipelineCreateInfo& GraphicsPipelineCreateInfo::DepthStencilState(VkPipelineDepthStencilStateCreateInfo const* _createInfo)
    {
        pDepthStencilState = _createInfo;
        return *this;
        // TODO: return ステートメントをここに挿入します
    }
    GraphicsPipelineCreateInfo& GraphicsPipelineCreateInfo::ColorBlendState(VkPipelineColorBlendStateCreateInfo const* _createInfo)
    {
        pColorBlendState = _createInfo;
        return *this;
        // TODO: return ステートメントをここに挿入します
    }
    GraphicsPipelineCreateInfo& GraphicsPipelineCreateInfo::DynamicState(VkPipelineDynamicStateCreateInfo const* _createInfo)
    {
        pDynamicState = _createInfo;
        return *this;
        // TODO: return ステートメントをここに挿入します
    }
    GraphicsPipelineCreateInfo& GraphicsPipelineCreateInfo::PipelineLayout(PipelineLayoutHandle const _layout)
    {
        layout = _layout.GetVulkanHandle();
        return *this;
        // TODO: return ステートメントをここに挿入します
    }
    GraphicsPipelineCreateInfo& GraphicsPipelineCreateInfo::ShaderStages(VkPipelineShaderStageCreateInfo const* _shaders, uint32_t _count)
    {
        pStages = _shaders;
        stageCount = _count;
        return *this;
        // TODO: return ステートメントをここに挿入します
    }
    GraphicsPipelineCreateInfo& GraphicsPipelineCreateInfo::RenderPass(RenderPassHandle const _handle, uint32_t _subpass)
    {
        renderPass = _handle.GetVulkanHandle();
        subpass = _subpass;
        return *this;
        // TODO: return ステートメントをここに挿入します
    }
}
