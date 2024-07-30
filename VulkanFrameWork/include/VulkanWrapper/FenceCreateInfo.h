#pragma once
#include <vulkan/vulkan.h>

namespace VulkanWrapper {

class FenceCreateInfo
	:public VkFenceCreateInfo
{
public:
	FenceCreateInfo();
	FenceCreateInfo(VkFenceCreateFlags _flags);
private:

};
}
#include "VulkanWrapper/FenceCreateInfo.inl"