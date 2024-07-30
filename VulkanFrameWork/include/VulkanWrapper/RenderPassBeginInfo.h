#pragma once
#include <vulkan/vulkan.h>
#include "Lib/Container/Vector.h"
namespace VulkanWrapper{
	class RenderPassHandle;
	class FrameBufferHandle;

class RenderPassBeginInfo
	:public VkRenderPassBeginInfo
{
public:
	RenderPassBeginInfo(
		RenderPassHandle _renderPass,
		FrameBufferHandle _frameBuffer
	);
	RenderPassBeginInfo& SetArea(
		VkOffset2D _offset,
		VkExtent2D _extent
	);
	RenderPassBeginInfo& SetClearValues(
		uint32_t clearValueCount,
		float const** _color,
		float const* _depth = nullptr,
		uint32_t const* _stencil = nullptr
	);
private:
	Lib::Container::Vector<VkClearValue> m_clearValues;
};
}
#include "VulkanWrapper/RenderPassBeginInfo.inl"