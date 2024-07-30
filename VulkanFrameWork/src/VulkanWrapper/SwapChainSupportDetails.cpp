#include "VulkanWrapper/SwapChainSupportDetails.h"
#include "VulkanWrapper/Instance.h"
#include "VulkanWrapper/Surface.h"
namespace VulkanWrapper{
    SwapChainSupportDetails::SwapChainSupportDetails(PhysicalDeviceHandle _hPhysDev, SurfaceHandle _hSurface)
    {
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(_hPhysDev.GetVulkanHandle(), _hSurface.GetVulkanHandle(), &m_capabilities);
        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(_hPhysDev.GetVulkanHandle(), _hSurface.GetVulkanHandle(), &formatCount, nullptr);

        if (formatCount != 0) {
            m_formats.Resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(_hPhysDev.GetVulkanHandle(), _hSurface.GetVulkanHandle(), &formatCount, m_formats.Data());
        }
        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(_hPhysDev.GetVulkanHandle(), _hSurface.GetVulkanHandle(), &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            m_presentModes.Resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(_hPhysDev.GetVulkanHandle(), _hSurface.GetVulkanHandle(), &presentModeCount, m_presentModes.Data());
        }
    }
    SwapChainSupportDetails::~SwapChainSupportDetails(){

        }
    SwapChainSupportDetails::SwapChainSupportDetails(SwapChainSupportDetails&& _this)
        :m_capabilities(_this.m_capabilities)
        ,m_formats(std::move(_this.m_formats))
        ,m_presentModes(std::move(_this.m_presentModes))
    {
    }
    bool SwapChainSupportDetails::IsSwapChainSupported() const
    {
        return (!m_formats.Empty() && !m_presentModes.Empty());
    }
    VkSurfaceCapabilitiesKHR const& SwapChainSupportDetails::GetCapablities() const
    {
        return m_capabilities;
    }
    Lib::Container::Vector<VkSurfaceFormatKHR> const& SwapChainSupportDetails::GetFormats() const
    {
        return m_formats;
    }
    Lib::Container::Vector<VkPresentModeKHR> const& SwapChainSupportDetails::GetPresentModes() const
    {
        return m_presentModes;
    }
}
