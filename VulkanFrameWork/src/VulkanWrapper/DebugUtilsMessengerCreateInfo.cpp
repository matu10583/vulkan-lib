#include "VulkanWrapper/DebugUtilsMessengerCreateInfo.h"
namespace VulkanWrapper{
        DebugUtilsMessengerCreateInfo::~DebugUtilsMessengerCreateInfo(
        ){

        }
        DebugUtilsMessengerCreateInfo::DebugUtilsMessengerCreateInfo(
            PFN_vkDebugUtilsMessengerCallbackEXT callback,
            void* _pUserData
        )
        :VkDebugUtilsMessengerCreateInfoEXT()
        {
            sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            messageSeverity =
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            messageType =
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            pfnUserCallback = callback;
            pUserData = _pUserData;
        }
}
