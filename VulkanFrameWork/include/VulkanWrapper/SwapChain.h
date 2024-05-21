#pragma once
#include "VulkanWrapper/VulkanHandleBase.h"
#include <vulkan/vulkan.h>
#include "VulkanWrapper/Defines.h"
#include "VulkanWrapper/SwapChainImage.h"
namespace VulkanWrapper{
	class SurfaceHandle;
	class DeviceHandle;
	class SwapChainHandle
		:public VulkanHandleBase<VkSwapchainKHR>
	{
	public:
		SwapChainHandle();
		~SwapChainHandle();
		bool Init(
			DeviceHandle _hDev,
			SurfaceHandle _hSurface,
			VkPresentModeKHR _presentMode,
			uint32_t _minImageCount,
			SurfaceInfo2D _imageInfo,
			uint32_t* _pSharingQueueFamilyIndices,
			uint32_t _sharingQueueFamilyCount,
			VkSurfaceTransformFlagBitsKHR _transform
		);
		void Destroy(DeviceHandle _hDev);
		//void GetImage(DeviceHandle _hDev)
	private:

	};


class SwapChain
{
        public:
        SwapChain();
        ~SwapChain();
		bool Init(
			DeviceHandle _hDev,
			SurfaceHandle _hSurface,
			VkPresentModeKHR _presentMode,
			uint32_t _minImageCount,
			SurfaceInfo2D _imageInfo,
			uint32_t* _pSharingQueueFamilyIndices,
			uint32_t _sharingQueueFamilyCount,
			VkSurfaceTransformFlagBitsKHR _transform
		);
		void Destroy(
			DeviceHandle _hDev
		);
private:
	SwapChainHandle m_swapChain;
	SwapChainImage m_images;
};
}
