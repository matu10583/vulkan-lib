#pragma once
#include "VulkanWrapper/VulkanHandleBase.h"
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
    class DeviceHandle;
    class ImageHandle
        :public VulkanHandleBase<VkImage> {
    public:
        ImageHandle();
        ~ImageHandle();
        bool Init(VkImage const& _hImage);

        void Destroy(DeviceHandle _hDev);
    };
class Image
{
        public:
        Image();
        ~Image();

private:
    ImageHandle m_handle;
};
}
