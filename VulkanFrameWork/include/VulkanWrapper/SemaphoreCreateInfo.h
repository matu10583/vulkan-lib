#pragma once
#include <vulkan/vulkan.h>

namespace VulkanWrapper{

class SemaphoreCreateInfo
	:public VkSemaphoreCreateInfo
{
public:
	SemaphoreCreateInfo();
private:

};
}
#include "VulkanWrapper/SemaphoreCreateInfo.inl"