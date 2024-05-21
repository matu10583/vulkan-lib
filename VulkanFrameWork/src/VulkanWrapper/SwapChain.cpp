#include "VulkanWrapper/SwapChain.h"
#include "VulkanWrapper/Surface.h"
#include "VulkanWrapper/Macro.h"
#include "VulkanWrapper/Device.h"
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
            return true;
        }
        void SwapChain::Destroy(DeviceHandle _hDev)
        {
            m_images.Destroy(_hDev);
            m_swapChain.Destroy(_hDev);
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
}
