#include "VulkanWrapper/ImageView.h"
#include "VulkanWrapper/Image.h"
#include "VulkanWrapper/Macro.h"
#include "VulkanWrapper/Device.h"
namespace VulkanWrapper{
        ImageView::~ImageView(){

        }
        ImageView::ImageView()
        {

        }
        ImageViewHandle::ImageViewHandle()
        {
        }
        ImageViewHandle::~ImageViewHandle()
        {
        }
        void ImageViewHandle::Destroy(DeviceHandle _hDev)
        {
            vkDestroyImageView(_hDev.GetVulkanHandle(), m_vkHandle, nullptr);
        }
        bool ImageViewHandle::Init(DeviceHandle _hDev, ImageHandle _hImage, VkImageViewType _type, VkFormat _format, VkImageSubresourceRange const& _range)
        {
            VkImageViewCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.image = _hImage.GetVulkanHandle();
            createInfo.viewType = _type;
            createInfo.format = _format;
            createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.subresourceRange = _range;

            VEXCEPT(
                vkCreateImageView(
                    _hDev.GetVulkanHandle(), &createInfo, nullptr, &m_vkHandle
                )
            );
            return true;
        }
}
