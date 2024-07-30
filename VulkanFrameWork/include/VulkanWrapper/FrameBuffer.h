#pragma once
#include "VulkanWrapper/VulkanHandleBase.h"

namespace VulkanWrapper{
	class DeviceHandle;

class FrameBufferHandle
	:public VulkanHandleBase<VkFramebuffer>
{
public:
	bool Init(
		DeviceHandle _dev,
		VkFramebufferCreateInfo const& _createInfo
	);
	void Destroy(DeviceHandle _dev);
private:

};
}
#include "VulkanWrapper/FrameBuffer.inl"