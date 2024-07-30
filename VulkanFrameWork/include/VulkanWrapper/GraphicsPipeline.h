#pragma once
#include <vulkan/vulkan.h>
#include "VulkanWrapper/VulkanHandleBase.h"

namespace VulkanWrapper{
    class DeviceHandle;
    class GrapchicsPipelineHandle
        :public VulkanHandleBase<VkPipeline>
    {
    public:
        GrapchicsPipelineHandle(){}
        ~GrapchicsPipelineHandle(){}

        bool Init(
            DeviceHandle _dev,
            VkGraphicsPipelineCreateInfo const* _createInfo
        );
        void Destroy(DeviceHandle _dev);
    };
class GraphicsPipeline
{
        public:
        GraphicsPipeline();
        ~GraphicsPipeline();
};
}
