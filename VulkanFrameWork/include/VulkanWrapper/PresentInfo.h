#pragma once
#include <vulkan/vulkan.h>

namespace VulkanWrapper{
	class SemaphoreHandle;
	class SwapChainHandle;
class PresentInfo
	:public VkPresentInfoKHR
{
public:
	PresentInfo();
	PresentInfo& WaitSemaphore(
		uint32_t _semaphoreCount,
		SemaphoreHandle* _pSemaphores
	);
	PresentInfo& SwapChainImages(
		uint32_t _scCount,
		SwapChainHandle* _scHandles,
		uint32_t* _pImageIndices
	);

private:

};
}
#include "VulkanWrapper/PresentInfo.inl"