#pragma once
namespace VulkanWrapper{
	inline VulkanWrapper::SemaphoreCreateInfo::SemaphoreCreateInfo()
		:VkSemaphoreCreateInfo()
	{
		sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	}
}
