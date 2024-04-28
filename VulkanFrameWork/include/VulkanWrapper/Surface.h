#pragma once
#ifdef VK_USE_PLATFORM_WIN32_KHR
#include <Windows.h>
#endif // VK_USE_PLATFORM_WIN32_KHR
#include "VulkanWrapper/Macro.h"

#include "VulkanWrapper/VulkanHandleBase.h"
namespace VulkanWrapper{
    class InstanceHandle;
class SurfaceHandle
:
public VulkanWrapper::VulkanHandleBase<VkSurfaceKHR>
{
public:
        SurfaceHandle();
        ~SurfaceHandle();

#ifdef VK_USE_PLATFORM_WIN32_KHR
        bool Init(
            InstanceHandle _handle,
            HWND _hwnd,
            HINSTANCE _hinst
        ) {
            VkWin32SurfaceCreateInfoKHR createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
            createInfo.hinstance = _hinst;
            createInfo.hwnd = _hwnd;

            VEXCEPT(
                vkCreateWin32SurfaceKHR(
                    _handle.GetVulkanHandle(), &createInfo, nullptr, &m_vkHandle
                )
            );
            return true;
        }
#endif // !1
        void Destroy(
            InstanceHandle _handle
        );
};
}
