#include "VulkanWrapper/SwapChain.h"
#include "VulkanWrapper/Surface.h"
#include "VulkanWrapper/Macro.h"
#include "VulkanWrapper/Device.h"
#include "VulkanWrapper/Semahore.h"
#include "VulkanWrapper/Fence.h"
namespace VulkanWrapper{
        SwapChain::~SwapChain(){

        }
        bool SwapChain::Init(DeviceHandle _hDev, SurfaceHandle _hSurface, VkPresentModeKHR _presentMode, uint32_t _minImageCount, SurfaceInfo2D _imageInfo, uint32_t* _pSharingQueueFamilyIndices, uint32_t _sharingQueueFamilyCount, VkSurfaceTransformFlagBitsKHR _transform)
        {
            m_swapChain.Init(
                _hDev,
                _hSurface,
                _presentMode,
                _minImageCount,
                _imageInfo,
                _pSharingQueueFamilyIndices,
                _sharingQueueFamilyCount,
                _transform
            );
            m_images.Init(
                _hDev, m_swapChain, _imageInfo.Image.Format
            );
            m_surfaceInfo = _imageInfo;
            return true;
        }
        void SwapChain::Destroy(DeviceHandle _hDev)
        {
            m_images.Destroy(_hDev);
            m_swapChain.Destroy(_hDev);
        }
        uint32_t SwapChain::GetImageCount() const
        {
            return m_images.GetImageCount();
        }
        ImageViewHandle SwapChain::GetImageHandle(uint32_t _t)
        {
            return m_images.GetImageView(_t);
        }

        VkExtent2D SwapChain::GetExtent2D() const
        {
            return m_surfaceInfo.Image.Extent;
        }

        VkFormat SwapChain::GetFormat() const
        {
            return m_surfaceInfo.Image.Format;
        }

        uint32_t SwapChain::AcquireNextImageIndex(DeviceHandle _dev, uint64_t _timeOut, SemaphoreHandle _semaphore, FenceHandle _fence)
        {
            return m_swapChain.AcquireNextImageIndex(
                _dev, _timeOut, _semaphore, _fence
            );
        }

        SwapChain::SwapChain()
                {

        }
        SwapChainHandle::SwapChainHandle()
        {
        }
        SwapChainHandle::~SwapChainHandle()
        {
        }
        bool 
            SwapChainHandle::Init(
                DeviceHandle _devHandle,
                SurfaceHandle _hSurface, 
                VkPresentModeKHR _presentMode,
                uint32_t _minImageCount, 
                SurfaceInfo2D _imageInfo, 
                uint32_t* _pSharingQueueFamilyIndices,
                uint32_t _sharingQueueFamilyCount, 
                VkSurfaceTransformFlagBitsKHR _transform)
        {
            VkSwapchainCreateInfoKHR createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
            createInfo.surface = _hSurface.GetVulkanHandle();
            createInfo.minImageCount = _minImageCount;
            createInfo.imageFormat = _imageInfo.Image.Format;
            createInfo.imageColorSpace = _imageInfo.ColorSpace;
            createInfo.imageExtent = _imageInfo.Image.Extent;
            createInfo.imageArrayLayers = 1;
            createInfo.imageUsage = _imageInfo.Image.Usage;
            if (_pSharingQueueFamilyIndices == nullptr || _sharingQueueFamilyCount == 0) {
                createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
                createInfo.queueFamilyIndexCount = 0;
                createInfo.pQueueFamilyIndices = nullptr;
            }
            else {
                createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
                createInfo.queueFamilyIndexCount = _sharingQueueFamilyCount;
                createInfo.pQueueFamilyIndices = _pSharingQueueFamilyIndices;
            }
            createInfo.preTransform = _transform;
            createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
            createInfo.presentMode = _presentMode;
            createInfo.clipped = VK_TRUE;
            createInfo.oldSwapchain = VK_NULL_HANDLE;

            VEXCEPT(vkCreateSwapchainKHR(
                _devHandle.GetVulkanHandle(), &createInfo, nullptr, &m_vkHandle
            ));
            return true;
        }
        void SwapChainHandle::Destroy(DeviceHandle _hDev)
        {
            vkDestroySwapchainKHR(_hDev.GetVulkanHandle(), m_vkHandle, nullptr);
        }
        uint32_t SwapChainHandle::AcquireNextImageIndex(DeviceHandle _dev, uint64_t _timeOut, SemaphoreHandle _semaphore, FenceHandle _fence)
        {
            uint32_t ret = UINT32_MAX;
            VEXCEPT(vkAcquireNextImageKHR(
                _dev.GetVulkanHandle(),
                m_vkHandle, _timeOut,
                _semaphore.GetVulkanHandle(),
                _fence.GetVulkanHandle(),
                &ret
            ));
            return ret;
        }
}
