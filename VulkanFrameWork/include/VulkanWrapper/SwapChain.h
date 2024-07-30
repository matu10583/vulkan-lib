#pragma once
#include "VulkanWrapper/VulkanHandleBase.h"
#include <vulkan/vulkan.h>
#include "VulkanWrapper/Defines.h"
#include "VulkanWrapper/SwapChainImage.h"
namespace VulkanWrapper{
	class SurfaceHandle;
	class DeviceHandle;
	class SemaphoreHandle;
	class FenceHandle;
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
		uint32_t AcquireNextImageIndex(
			DeviceHandle _dev,
			uint64_t _timeOut,
			SemaphoreHandle _semaphore,
			FenceHandle _fence
		);
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
		uint32_t GetImageCount()const;
		ImageViewHandle GetImageHandle(uint32_t _t);
		VkExtent2D GetExtent2D()const;
		VkFormat GetFormat()const;
		uint32_t AcquireNextImageIndex(
			DeviceHandle _dev,
			uint64_t _timeOut,
			SemaphoreHandle _semaphore,
			FenceHandle _fence
		);
private:
	SwapChainHandle m_swapChain;
	SwapChainImage m_images;
	SurfaceInfo2D m_surfaceInfo;
};
}
