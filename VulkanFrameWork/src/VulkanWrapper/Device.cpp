#include "VulkanWrapper/Device.h"
#include "Lib/Container/StaticVector.h"
#include "VulkanWrapper/Macro.h"

namespace VulkanWrapper {
	DeviceHandle::DeviceHandle()
	{
	}
	DeviceHandle::~DeviceHandle()
	{
	}
	bool DeviceHandle::Init(
		PhysicalDeviceHandle Device,
		VkPhysicalDeviceFeatures const& feats,
		VkDeviceQueueCreateInfo const* infos,
		uint32_t queueCreateInfoCount,
		char const** ppEnabledExtensions,
		uint32_t extensionCount,
		char const** ppEnabledLayers,
		uint32_t layerCount)
	{

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pEnabledFeatures = &feats;
		createInfo.pQueueCreateInfos = infos;
		createInfo.queueCreateInfoCount = queueCreateInfoCount;
		createInfo.enabledExtensionCount = extensionCount;
		createInfo.ppEnabledExtensionNames = ppEnabledExtensions;
		createInfo.enabledLayerCount = layerCount;
		createInfo.ppEnabledLayerNames = ppEnabledLayers;
		VEXCEPT(
			vkCreateDevice(
				Device.GetVulkanHandle(), &createInfo, nullptr, &m_vkHandle
			)
		);

		return true;
	}

	void DeviceHandle::Destroy()
	{
		vkDestroyDevice(
			m_vkHandle, nullptr
		);
	}

	void DeviceHandle::WaitIdle()
	{
		vkDeviceWaitIdle(m_vkHandle);
	}

	void DeviceHandle::GetDeviceQueue(uint32_t _family_idx, uint32_t _idx, QueueHandle* _pHandle)
	{
		vkGetDeviceQueue(m_vkHandle, _family_idx, _idx, _pHandle->VulkanHandleData());
	}


	Device::Device()
	{
	}

	Device::~Device()
	{
	}

	bool Device::Init(
		PhysicalDeviceHandle Device, VkPhysicalDeviceFeatures const& feats,
		VkDeviceQueueCreateInfo const* infos, uint32_t queueCreateInfoCount,
		char const** ppEnabledExtensions, uint32_t extensionCount, 
		char const** ppEnabledLayers, uint32_t layerCount)
	{
		m_phys = Device;
		m_extensions.Clear();
		m_extensions.Resize(extensionCount);
		for (uint32_t i = 0u; i < extensionCount; i++) {
			bool result = m_extensions[i].Copy(ppEnabledExtensions[i]);
			assert(result);
		}
		m_layers.Clear();
		m_layers.Resize(layerCount);
		for (uint32_t i = 0u; i < layerCount; i++) {
			bool result = m_layers[i].Copy(ppEnabledLayers[i]);
			assert(result);
		}
		m_device.Init(
			Device,
			feats, infos, queueCreateInfoCount,
			ppEnabledExtensions, extensionCount,
			ppEnabledLayers, layerCount
		);

		return true;
	}

	void Device::WaitIdle()
	{
		m_device.WaitIdle();
	}

	void Device::Destroy()
	{
		m_device.Destroy();
	}

	void Device::GetQueue(uint32_t _family_idx, uint32_t _idx, Queue* _pQueue)
	{
		m_device.GetDeviceQueue(_family_idx, _idx, &_pQueue->m_queue);
	}

	DeviceHandle Device::GetHandle() const
	{
		return m_device;
	}

	PhysicalDeviceHandle Device::GetPhysicalDevice() const
	{
		return m_phys;
	}

}
