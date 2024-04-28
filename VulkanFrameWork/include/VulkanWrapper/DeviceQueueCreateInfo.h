#pragma once
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
class DeviceQueueCreateInfo
: public VkDeviceQueueCreateInfo
{
public:
	DeviceQueueCreateInfo()
		:VkDeviceQueueCreateInfo() {
		sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	}
};
}

