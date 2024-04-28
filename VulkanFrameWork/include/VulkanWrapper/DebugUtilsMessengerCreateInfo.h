#pragma once
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
class DebugUtilsMessengerCreateInfo
:
public VkDebugUtilsMessengerCreateInfoEXT
{
public:
        DebugUtilsMessengerCreateInfo(
            PFN_vkDebugUtilsMessengerCallbackEXT callback,
            void* pUserData = nullptr
        );
        ~DebugUtilsMessengerCreateInfo();
};
}
