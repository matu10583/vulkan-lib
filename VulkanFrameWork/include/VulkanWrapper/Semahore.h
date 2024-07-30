#pragma once
#include "VulkanWrapper/VulkanHandleBase.h"

namespace VulkanWrapper{
	class DeviceHandle;
class SemaphoreHandle
	:public VulkanHandleBase<VkSemaphore>
{
public:
	bool Init(
		DeviceHandle _dev,
		VkSemaphoreCreateInfo const* _createInfo
	);
	void Destroy(
		DeviceHandle _dev
	);
private:

};
}
#include "VulkanWrapper/Semahore.inl"