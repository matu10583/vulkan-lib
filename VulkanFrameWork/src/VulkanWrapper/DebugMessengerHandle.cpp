#include "VulkanWrapper/DebugMessengerHandle.h"
#include "VulkanWrapper/Macro.h"
#include "VulkanWrapper/Instance.h"
namespace VulkanWrapper{
        DebugMessengerHandle::~DebugMessengerHandle(){

        }
        bool DebugMessengerHandle::Init(
            InstanceHandle handle,
            VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo)
        {
            VEXCEPT(
                CreateDebugUtilsMessangerExt(
                    handle.GetVulkanHandle(),
                    pCreateInfo, nullptr,
                    &m_vkHandle
                )
            );
            return true;
        }
        void DebugMessengerHandle::Destroy(InstanceHandle handle)
        {
            DestroyDebugUtilsMessangerExt(
                handle.GetVulkanHandle(),
                m_vkHandle, nullptr
            );
        }
        DebugMessengerHandle::DebugMessengerHandle()
        :VulkanWrapper::VulkanHandleBase<VkDebugUtilsMessengerEXT>()
,VulkanWrapper::ExtFunctionDispatchable()
        {

        }
}
