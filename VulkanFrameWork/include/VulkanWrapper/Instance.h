#pragma once
#include <vulkan/vulkan.h>
#include <cstdint>
#include "VulkanWrapper/HandleWrapper.h"
#include "VulkanWrapper/IInstance.h"
#include "Lib/Container/Vector.h"
#include "Lib/Container/StaticString.h"

#ifndef MAX_EXTENSION_NAME_LENGTH
#define MAX_EXTENSION_NAME_LENGTH 30
#endif // !MAX_EXTENSION_NAME_LENGTH
#ifndef MAX_LAYER_NAME_LENGTH
#define MAX_LAYER_NAME_LENGTH 30
#endif // !MAX_LAYER_NAME_LENGTH


namespace VulkanWrapper {
	class IApplication;
	class InstanceHandle
	{
	public:
		InstanceHandle();
		~InstanceHandle();
		bool Init(
			uint32_t apiVersion,
			IApplication const* pApp,
			char const** ppEnableLayerName,
			uint32_t const layerCount,
			char const** ppEnableExtensionName,
			uint32_t const extensionCount);
		void Destroy();
	private:
		VkInstance m_vkInstance;
	};

	class Instance
		:public IInstance
	{
	public:
		Instance();
		~Instance();
		bool Init(
			uint32_t apiVersion,
			IApplication const* pApp,
			char const** ppEnableLayerName,
			uint32_t const layerCount,
			char const** ppEnableExtensionName,
			uint32_t const extensionCount);
		void Destroy();
		InstanceHandle GetHandle() const;
	private:
		InstanceHandle m_instance;
		//extension,layer‚Ì–¼‘O‚ðŠo‚¦‚Ä‚¨‚­
		Lib::Container::Vector<
			Lib::Container::StaticString<MAX_EXTENSION_NAME_LENGTH>> m_extensions;
		Lib::Container::Vector<
			Lib::Container::StaticString<MAX_LAYER_NAME_LENGTH>> m_layers;

	};
}

