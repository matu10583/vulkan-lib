#include "VulkanWrapper/PipelineLayout.h"
#include "VulkanWrapper/Macro.h"
#include "VulkanWrapper/Device.h"

namespace VulkanWrapper{
    PipelineLayoutHandle::PipelineLayoutHandle()
    {

    }
    PipelineLayoutHandle::~PipelineLayoutHandle()
    {
    }
    bool PipelineLayoutHandle::Init(DeviceHandle _handle)
    {
        VkPipelineLayoutCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        createInfo.setLayoutCount = 0;
        createInfo.pSetLayouts = nullptr;
        createInfo.pushConstantRangeCount = 0;
        createInfo.pPushConstantRanges = nullptr;

        VEXCEPT(
            vkCreatePipelineLayout(_handle.GetVulkanHandle(),
                &createInfo, nullptr, &m_vkHandle)
        );
        return true;
    }
    void PipelineLayoutHandle::Destroy(DeviceHandle _handle)
    {
        vkDestroyPipelineLayout(_handle.GetVulkanHandle(), m_vkHandle, nullptr);
    }
}
