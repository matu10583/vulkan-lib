#include "VulkanWrapper/SubmitInfo.h"
#include "VulkanWrapper/Semahore.h"
#include "VulkanWrapper/CommandBuffer.h"

namespace VulkanWrapper{
	SubmitInfo::SubmitInfo()
		:VkSubmitInfo()
	{
		sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	}
	SubmitInfo& SubmitInfo::WaitSemaphore(uint32_t _semaphoreCount,
		SemaphoreHandle* _pSemaphores,
		VkPipelineStageFlags* _waitStgs)
	{
		waitSemaphoreCount = _semaphoreCount;
		pWaitSemaphores = _pSemaphores->VulkanHandleData();
		pWaitDstStageMask = _waitStgs;
		return *this;
		// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
	}
	SubmitInfo& SubmitInfo::SignalSemaphore(uint32_t _semaphoreCount, SemaphoreHandle* _pSemaphores)
	{
		signalSemaphoreCount = _semaphoreCount;
		pSignalSemaphores = _pSemaphores->VulkanHandleData();
		return *this;
		// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
	}
	SubmitInfo& SubmitInfo::CommandBuffer(uint32_t _bufferCount, CommandBufferHandle* _pCmdBuffs)
	{
		commandBufferCount = _bufferCount;
		pCommandBuffers = _pCmdBuffs->VulkanHandleData();
		return *this;
		// TODO: return �X�e�[�g�����g�������ɑ}�����܂�
	}
}
