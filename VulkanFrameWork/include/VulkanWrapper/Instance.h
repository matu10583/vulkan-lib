#pragma once
#include <vulkan/vulkan.h>
#include <cstdint>
#include "Lib/Container/Vector.h"
#include "Lib/Container/StaticString.h"
#include "VulkanWrapper/VulkanHandleBase.h"
#include "VulkanWrapper/ExtFunctionDispatchable.h"
#include "VulkanWrapper/DebugMessengerHandle.h"

#ifndef MAX_EXTENSION_NAME_LENGTH
#define MAX_EXTENSION_NAME_LENGTH 30
#endif // !MAX_EXTENSION_NAME_LENGTH
#ifndef MAX_LAYER_NAME_LENGTH
#define MAX_LAYER_NAME_LENGTH 30
#endif // !MAX_LAYER_NAME_LENGTH


namespace VulkanWrapper {
	class IApplication;
	class PhysicalDeviceHandle;
	class InstanceHandle
		:public VulkanHandleBase<VkInstance>
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
			uint32_t const extensionCount
#ifdef _DEBUG
			, VkDebugUtilsMessengerCreateInfoEXT const* debugCreateInfo
#endif // _DEBUG
		);
		void EnumeratePhysicalDevices(
			PhysicalDeviceHandle* outPhys, uint32_t physCount
		);
		uint32_t GetPhysicalDeviceCount();
		void Destroy();
	};

	class PhysicalDeviceHandle
		:public VulkanHandleBase<VkPhysicalDevice>
	{
	public:
		PhysicalDeviceHandle();
		~PhysicalDeviceHandle();
		VkPhysicalDeviceProperties GetProperties()const;
		VkPhysicalDeviceFeatures GetFeatures()const;
		void GetQueueFamilyProperties(
			VkQueueFamilyProperties* pOutProps, uint32_t count
		)const;
		uint32_t GetQueueFamilyCount()const;
	};


	class Instance
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
			uint32_t const extensionCount
#ifdef _DEBUG
			, PFN_vkDebugUtilsMessengerCallbackEXT debugCallback
			, void* pUserData = nullptr
#endif // _DEBUG
		
		);
		void Destroy();
		InstanceHandle GetHandle() const;
		PhysicalDeviceHandle GetPhyscalDevice(uint32_t idx);
		uint32_t GetPhysicalDeviceCount();
		uint32_t GetLayers(char const** pOutArray, uint32_t buff_size);
		uint32_t GetLayerLength()const;
	private:
		InstanceHandle m_instance;
#ifdef _DEBUG
		DebugMessengerHandle m_debugMessanger;
#endif // _DEBUG

		//extension,layer‚Ì–¼‘O‚ðŠo‚¦‚Ä‚¨‚­
		Lib::Container::Vector<
			Lib::Container::StaticString<MAX_EXTENSION_NAME_LENGTH>> m_extensions;
		Lib::Container::Vector<
			Lib::Container::StaticString<MAX_LAYER_NAME_LENGTH>> m_layers;
		Lib::Container::Vector<PhysicalDeviceHandle> m_physDevices;
	};
}

