#pragma once
#include <vulkan/vulkan.h>

namespace VulkanWrapper{
	class SemaphoreHandle;
	class CommandBufferHandle;
class SubmitInfo
	:public VkSubmitInfo
{
public:
	SubmitInfo();
	SubmitInfo& WaitSemaphore(uint32_t _semaphoreCount, 
		SemaphoreHandle* _pSemaphores,
		VkPipelineStageFlags* _waitStgs);
	SubmitInfo& SignalSemaphore(uint32_t _semaphoreCount,
		SemaphoreHandle* _pSemaphores);
	SubmitInfo& CommandBuffer(uint32_t _bufferCount,
		CommandBufferHandle* _pCmdBuffs);
private:

};
}
#include "VulkanWrapper/SubmitInfo.inl"