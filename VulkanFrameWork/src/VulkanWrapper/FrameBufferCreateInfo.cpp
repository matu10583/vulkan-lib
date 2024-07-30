#include "VulkanWrapper/FrameBufferCreateInfo.h"
#include "VulkanWrapper/Device.h"
#include "VulkanWrapper/RenderPass.h"
#include "VulkanWrapper/ImageView.h"
namespace VulkanWrapper{
    FrameBufferCreateInfo::FrameBufferCreateInfo(RenderPassHandle _renderPass, ImageViewHandle* _pImageViewHandles, uint32_t _imageViewCount, VkExtent2D const& _size, uint32_t _layers)
        :FrameBufferCreateInfo()
    {
        renderPass = _renderPass.GetVulkanHandle();
        attachmentCount = _imageViewCount;
        pAttachments = reinterpret_cast<VkImageView*>(_pImageViewHandles);
        width = _size.width;
        height = _size.height;
        layers = _layers;
    }
    FrameBufferCreateInfo::FrameBufferCreateInfo()
        :VkFramebufferCreateInfo()
    {
        sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    }
}
