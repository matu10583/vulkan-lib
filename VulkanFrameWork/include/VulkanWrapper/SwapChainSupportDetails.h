#pragma once
#include "Lib/Container/Vector.h"
#include "vulkan/vulkan.h"
namespace VulkanWrapper{
    class PhysicalDeviceHandle;
    class SurfaceHandle;
class SwapChainSupportDetails
{
        public:
        SwapChainSupportDetails(PhysicalDeviceHandle _hPhysDev, SurfaceHandle _hSurface);
        ~SwapChainSupportDetails();
        SwapChainSupportDetails(SwapChainSupportDetails&&);
        bool IsSwapChainSupported()const;
        VkSurfaceCapabilitiesKHR const& GetCapablities()const;
        Lib::Container::Vector<VkSurfaceFormatKHR> const& GetFormats()const;
        Lib::Container::Vector<VkPresentModeKHR> const& GetPresentModes()const;
private:
    VkSurfaceCapabilitiesKHR m_capabilities;
    Lib::Container::Vector<VkSurfaceFormatKHR> m_formats;
    Lib::Container::Vector<VkPresentModeKHR> m_presentModes;
};
}
