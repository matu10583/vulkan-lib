#include "VulkanWrapper/Image.h"
#include "VulkanWrapper/Device.h"
namespace VulkanWrapper{
        Image::~Image(){

        }
        Image::Image()
                {

        }
        ImageHandle::ImageHandle()
        {

        }

        ImageHandle::~ImageHandle()
        {
        }
        bool ImageHandle::Init(VkImage const& _hImage)
        {
            m_vkHandle = _hImage;
            return true;
        }
        void ImageHandle::Destroy(DeviceHandle _hDev)
        {
            vkDestroyImage(_hDev.GetVulkanHandle(), m_vkHandle, nullptr);
        }
}
