#include "VulkanWrapper/CommandBuffer.h"
#include "VulkanWrapper/Macro.h"
#include "VulkanWrapper/GraphicsPipeline.h"

namespace VulkanWrapper{
    void CommandBufferHandle::CmdBegin(VkCommandBufferBeginInfo const* _beginInfo)
    {
        VEXCEPT(
            vkBeginCommandBuffer(
                m_vkHandle, _beginInfo
            )
        );
    }
    void CommandBufferHandle::CmdBeginRenderPass(VkRenderPassBeginInfo const* _beginInfo, VkSubpassContents _contents)
    {
        vkCmdBeginRenderPass(
            m_vkHandle, _beginInfo, _contents
        );
    }
    void CommandBufferHandle::CmdBindGraphicPipeline(GrapchicsPipelineHandle _pipeline)
    {
        vkCmdBindPipeline(
            m_vkHandle, VK_PIPELINE_BIND_POINT_GRAPHICS,
            _pipeline
        );
    }
    void CommandBufferHandle::CmdSetViewPort(VkViewport const* _viewPort, uint32_t _viewPortCount)
    {
        vkCmdSetViewport(
            m_vkHandle, 0, _viewPortCount,
            _viewPort
        );
    }
    void CommandBufferHandle::CmdSetScissor(VkRect2D const* _scissor, uint32_t _scissorCount)
    {
        vkCmdSetScissor(
            m_vkHandle, 0, _scissorCount,
            _scissor
        );
    }
    void CommandBufferHandle::CmdDraw(uint32_t _vertexCount, uint32_t _instanceCount, uint32_t _firstVertex, uint32_t _firstInstance)
    {
        vkCmdDraw(
            m_vkHandle, _vertexCount, _instanceCount, _firstVertex, _firstInstance
        );
    }
    void CommandBufferHandle::CmdEndRenderPass()
    {
        vkCmdEndRenderPass(m_vkHandle);
    }
    void CommandBufferHandle::CmdEnd()
    {
        VEXCEPT(
            vkEndCommandBuffer(
                m_vkHandle
            )
        );
    }
    void CommandBufferHandle::Reset(VkCommandBufferResetFlags _flags)
    {
        VEXCEPT(vkResetCommandBuffer(
            m_vkHandle, _flags
        ));
    }
}
