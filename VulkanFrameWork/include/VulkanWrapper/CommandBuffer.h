#pragma once
#include "VulkanWrapper/VulkanHandleBase.h"


namespace VulkanWrapper{
	class GrapchicsPipelineHandle;
	class CommandBufferHandle
		:public VulkanHandleBase<VkCommandBuffer>
	{
	public:
		void CmdBegin(
			VkCommandBufferBeginInfo const* _beginInfo
		);
		void CmdBeginRenderPass(
			VkRenderPassBeginInfo const* _beginInfo,
			VkSubpassContents _contents
		);
		void CmdBindGraphicPipeline(
			GrapchicsPipelineHandle _pipeline
		);
		void CmdSetViewPort(
			VkViewport const* _viewPort,
			uint32_t _viewPortCount
		);
		void CmdSetScissor(
			VkRect2D const* _scissor,
			uint32_t _scissorCount
		);
		void CmdDraw(
			uint32_t _vertexCount, uint32_t _instanceCount,
			uint32_t _firstVertex, uint32_t _firstInstance
		);
		void CmdEndRenderPass();
		void CmdEnd();
		void Reset(VkCommandBufferResetFlags _flags);
	private:

	};

class CommandBuffer
{
public:

private:

};
}
#include "VulkanWrapper/CommandBuffer.inl"