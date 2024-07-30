#pragma once
#include "VulkanWrapper/VulkanHandleBase.h"
namespace VulkanWrapper{
	class DeviceHandle;
	class CommandPoolHandle 
		:public VulkanHandleBase<VkCommandPool>
	{
	public:
		bool Init(
			DeviceHandle _device,
		VkCommandPoolCreateInfo const& _createInfo);
		void Destroy(DeviceHandle _device);

	private:

	};

class CommandPool
{
public:

private:

};
}
#include "VulkanWrapper/CommandPool.inl"