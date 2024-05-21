#include "VulkanWrapper/InstanceLayerSupport.h"
namespace VulkanWrapper{
        InstanceLayerSupport::~InstanceLayerSupport(){

        }
        InstanceLayerSupport::InstanceLayerSupport()
                {
            uint32_t layercount;
            vkEnumerateInstanceLayerProperties(&layercount, nullptr);
            m_properties.Resize(layercount);

            vkEnumerateInstanceLayerProperties(&layercount, m_properties.Data());
        }
}
