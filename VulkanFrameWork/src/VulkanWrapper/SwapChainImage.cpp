#include "VulkanWrapper/SwapChainImage.h"
#include "VulkanWrapper/Device.h"
#include "VulkanWrapper/SwapChain.h"
namespace VulkanWrapper{
        SwapChainImage::~SwapChainImage(){

        }
        bool SwapChainImage::Init(DeviceHandle _hDev, SwapChainHandle _hSC, VkFormat _format)
        {
            uint32_t imageCount = 0;
            vkGetSwapchainImagesKHR(_hDev.GetVulkanHandle(), _hSC.GetVulkanHandle(), &imageCount, nullptr);
            m_images.Resize(imageCount);
            vkGetSwapchainImagesKHR(_hDev.GetVulkanHandle(), _hSC.GetVulkanHandle(), &imageCount, m_images[0].VulkanHandleData());

            m_imageViews.Resize(imageCount);
            VkImageSubresourceRange range{};
            range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            range.baseMipLevel = 0;
            range.levelCount = 1;
            range.baseArrayLayer = 0;
            range.layerCount = 1;
            for (uint32_t i = 0u; i < m_images.Length(); i++) {
                m_imageViews[i].Init(
                    _hDev, m_images[i], VK_IMAGE_VIEW_TYPE_2D, _format, range
                );
            }
            return true;
        }
        void SwapChainImage::Destroy(DeviceHandle _hDev)
        {
            for (uint32_t i = 0u; i < m_imageViews.Length(); i++) {
                m_imageViews[i].Destroy(_hDev);
            }
        }
        ImageHandle SwapChainImage::GetImage(uint32_t _i)
        {
            assert(_i < m_images.Length());
            return m_images[_i];
        }
        ImageViewHandle SwapChainImage::GetImageView(uint32_t _i)
        {
            assert(_i < m_imageViews.Length());
            return m_imageViews[_i];
        }
        uint32_t SwapChainImage::GetImageCount() const
        {
            return m_images.Length();
        }
        SwapChainImage::SwapChainImage()
                {

        }
}
