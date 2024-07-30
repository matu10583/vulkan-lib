#pragma once
#include <vulkan/vulkan.h>

namespace VulkanWrapper{
	class RenderPassHandle;
	class ImageViewHandle;
class FrameBufferCreateInfo
	:public VkFramebufferCreateInfo
{
public:
	FrameBufferCreateInfo();
	FrameBufferCreateInfo(
		RenderPassHandle _renderPass,
		ImageViewHandle* _pImageViewHandles,
		uint32_t _imageViewCount,
		VkExtent2D const& _size,
		uint32_t _layers
	);
private:

};
}
#include "VulkanWrapper/FrameBufferCreateInfo.inl"