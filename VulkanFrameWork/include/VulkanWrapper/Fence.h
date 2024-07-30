#pragma once
#include "VulkanWrapper/VulkanHandleBase.h"

namespace VulkanWrapper{
	class DeviceHandle;
class FenceHandle
	:public VulkanHandleBase<VkFence>
{
public:
	bool Init(
		DeviceHandle _device,
		VkFenceCreateInfo const* _pCreateInfo
	);
	void Destroy(DeviceHandle _dev);
private:

};
}
#include "VulkanWrapper/Fence.inl"