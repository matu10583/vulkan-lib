#include "VulkanWrapper/Surface.h"
#include "VulkanWrapper/Instance.h"
namespace VulkanWrapper{
        SurfaceHandle::~SurfaceHandle(){

        }
        void SurfaceHandle::Destroy(InstanceHandle _handle)
        {
            vkDestroySurfaceKHR(_handle.GetVulkanHandle(), m_vkHandle, nullptr);
        }
        SurfaceHandle::SurfaceHandle()
        :VulkanWrapper::VulkanHandleBase<VkSurfaceKHR>()
        {

        }
}
