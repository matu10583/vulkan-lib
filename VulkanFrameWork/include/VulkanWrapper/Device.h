#pragma once
#include "VulkanWrapper/VulkanHandleBase.h"
#include <vulkan/vulkan.h>
#include "VulkanWrapper/Instance.h"
namespace VulkanWrapper{
	class DeviceHandle: public VulkanHandleBase<VkDevice>
	{
	public:
		DeviceHandle();
		~DeviceHandle();
		bool Init(
			PhysicalDeviceHandle Device,
			VkPhysicalDeviceFeatures const& feats,
			VkDeviceQueueCreateInfo const* infos,
			uint32_t queueCreateInfoCount,
			char const** ppEnabledExtensions,
			uint32_t extensionCount,
			char const** ppEnabledLayers,
			uint32_t layerCount
		);
		void Destroy();
	private:

	};

class Device
{
public:
	Device();
	~Device();
	bool Init(
		PhysicalDeviceHandle Device,
		VkPhysicalDeviceFeatures const& feats,
		VkDeviceQueueCreateInfo const* infos,
		uint32_t queueCreateInfoCount,
		char const** ppEnabledExtensions,
		uint32_t extensionCount,
		char const** ppEnabledLayers,
		uint32_t layerCount
	);
private:
	PhysicalDeviceHandle m_phys;
	DeviceHandle m_device;
	//extension,layer‚Ì–¼‘O‚ðŠo‚¦‚Ä‚¨‚­
	Lib::Container::Vector<
		Lib::Container::StaticString<MAX_EXTENSION_NAME_LENGTH>> m_extensions;
	Lib::Container::Vector<
		Lib::Container::StaticString<MAX_LAYER_NAME_LENGTH>> m_layers;
};
}

