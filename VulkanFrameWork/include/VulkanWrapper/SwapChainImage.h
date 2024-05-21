#pragma once
#include "VulkanWrapper/Image.h"
#include "VulkanWrapper/ImageView.h"
#include "Lib/Container/Vector.h"
namespace VulkanWrapper{
    class DeviceHandle;
    class SwapChainHandle;
    class ImageHandle;
    class ImageViewHandle;
class SwapChainImage
{
 public:
    SwapChainImage();
    ~SwapChainImage();
    bool Init(DeviceHandle _hDev, SwapChainHandle _hSC, VkFormat _format);
    void Destroy(DeviceHandle _hDev);
    ImageHandle GetImage(uint32_t _i);
    ImageViewHandle GetImageView(uint32_t _i);
private:
    Lib::Container::Vector<ImageHandle> m_images;
    Lib::Container::Vector<ImageViewHandle> m_imageViews;
};
}
