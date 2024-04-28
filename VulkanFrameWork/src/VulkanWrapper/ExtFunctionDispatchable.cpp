#include "VulkanWrapper/ExtFunctionDispatchable.h"
namespace VulkanWrapper{
    VkResult ExtFunctionDispatchable::CreateDebugUtilsMessangerExt(VkInstance instance, VkDebugUtilsMessengerCreateInfoEXT const* pCreateInfo, VkAllocationCallbacks const* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
    {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        }
        else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }
    void ExtFunctionDispatchable::DestroyDebugUtilsMessangerExt(VkInstance instance, VkDebugUtilsMessengerEXT pDebugMessenger, VkAllocationCallbacks const* pAllocator)
    {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pDebugMessenger, pAllocator);
        }
    }
}

