#pragma once
#include <cstdint>

namespace VulkanWrapper {
	class IApplication
	{
	public:
		virtual uint32_t VkAppVersion()const = 0;
		virtual uint32_t VkEngineVersion()const = 0;
		virtual char const* VkApplicationName()const = 0;
		virtual char const* VkEngineName()const = 0;
	};
}


