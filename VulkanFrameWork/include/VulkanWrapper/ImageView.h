#pragma once
#include "VulkanWrapper/VulkanHandleBase.h"
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
    class ImageHandle;
    class DeviceHandle;
    class ImageViewHandle
        :public VulkanHandleBase<VkImageView>
    {
    public:
        ImageViewHandle();
        ~ImageViewHandle();
        bool Init(
            DeviceHandle _hDev,
            ImageHandle _hImage,
            VkImageViewType _type,
            VkFormat _format,
            VkImageSubresourceRange const& _range
        );
        void Destroy(DeviceHandle _hDev);
    };
class ImageView
{
public:
    ImageView();
    ~ImageView();

private:
    ImageViewHandle m_handle;
};
}
