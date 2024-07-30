#include "VulkanWrapper/GraphicsPipeline.h"
#include "VulkanWrapper/Macro.h"
#include "VulkanWrapper/Device.h"
namespace VulkanWrapper{
        GraphicsPipeline::~GraphicsPipeline(){

        }
        GraphicsPipeline::GraphicsPipeline()
                {

        }
        bool GrapchicsPipelineHandle::Init(
            DeviceHandle _dev,
            VkGraphicsPipelineCreateInfo const* _createInfo)
        {
            VEXCEPT(
                vkCreateGraphicsPipelines(
                    _dev.GetVulkanHandle(),
                    VK_NULL_HANDLE, 1,
                    _createInfo, nullptr, &m_vkHandle
                )
            );
            return true;
        }
        void GrapchicsPipelineHandle::Destroy(DeviceHandle _dev)
        {
            vkDestroyPipeline(
                _dev.GetVulkanHandle(),
                m_vkHandle, nullptr
            );
        }
}
