#pragma once
#include <vulkan/vulkan.h>

namespace VulkanWrapper{
	class DeviceHandle;
	class CommandBufferAllocateInfo;
	class CommandBufferHandle;
	bool AllocateCommandBuffer(
		DeviceHandle _device,
		CommandBufferAllocateInfo const& _createInfo,
		CommandBufferHandle* _outHandles
	);
}
#include "VulkanWrapper/Functions.inl"