#pragma once
#include "VulkanWrapper/VulkanHandleBase.h"

namespace VulkanWrapper{
	class DeviceHandle;
	class RenderPassHandle 
		:public VulkanHandleBase<VkRenderPass>
	{
	public:
		RenderPassHandle(){}
		~RenderPassHandle(){}

		bool Init(VkRenderPassCreateInfo const& _createInfo, DeviceHandle _dev);
		void Destroy(DeviceHandle _dev);
	};

class RenderPass
{
public:

private:

};
}
#include "VulkanWrapper/RenderPass.inl"