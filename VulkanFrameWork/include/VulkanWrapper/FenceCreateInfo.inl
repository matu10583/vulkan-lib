#include "FenceCreateInfo.h"
#pragma once
namespace VulkanWrapper{
	inline FenceCreateInfo::FenceCreateInfo()
		:VkFenceCreateInfo()
	{
		sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	}
	inline VulkanWrapper::FenceCreateInfo::FenceCreateInfo(VkFenceCreateFlags _flags)
		:FenceCreateInfo()
	{
		flags = _flags;
	}
}
