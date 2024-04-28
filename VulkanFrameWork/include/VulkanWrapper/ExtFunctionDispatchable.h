#pragma once
#include <vulkan/vulkan.h>

namespace VulkanWrapper{
class ExtFunctionDispatchable
{
protected:
	VkResult CreateDebugUtilsMessangerExt(
		VkInstance instance,
		VkDebugUtilsMessengerCreateInfoEXT const* pCreateInfo,
		VkAllocationCallbacks const* pAllocator,
		VkDebugUtilsMessengerEXT* pDebugMessenger
	);
	void DestroyDebugUtilsMessangerExt(VkInstance instance, VkDebugUtilsMessengerEXT pDebugMessenger, VkAllocationCallbacks const* pAllocator);
};
}

