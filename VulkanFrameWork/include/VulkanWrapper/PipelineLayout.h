#pragma once
#include "VulkanWrapper/VulkanHandleBase.h"
#include "vulkan/vulkan.h"

namespace VulkanWrapper{
    class DeviceHandle;
class PipelineLayoutHandle
    :public VulkanWrapper::VulkanHandleBase<VkPipelineLayout>
{
public:
    PipelineLayoutHandle();
    ~PipelineLayoutHandle();
    bool Init(DeviceHandle _handle);
    void Destroy(
        DeviceHandle _handle
    );
private:
};
}
#include "VulkanWrapper/PipelineLayout.inl"