#include "VulkanWrapper/Instance.h"
#include "VulkanWrapper/IApplication.h"
#include "VulkanWrapper/Macro.h"
#include "Lib/Utility/Math.h"
#include "VulkanWrapper/DebugUtilsMessengerCreateInfo.h"
VulkanWrapper::InstanceHandle::InstanceHandle()
{
}

VulkanWrapper::InstanceHandle::~InstanceHandle()
{
}

bool VulkanWrapper::InstanceHandle::Init(
	uint32_t apiVersion,
	IApplication const* pApp,
	char const** ppEnableLayerName,
	uint32_t const layerCount,
	char const** ppEnableExtensionName,
	uint32_t const extensionCount
#ifdef _DEBUG
	, VkDebugUtilsMessengerCreateInfoEXT const* debugCreateInfo
#endif // _DEBUG
)
{
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.apiVersion = apiVersion;
	appInfo.applicationVersion = pApp->VkAppVersion();
	appInfo.engineVersion = pApp->VkEngineVersion();
	appInfo.pApplicationName = pApp->VkApplicationName();
	appInfo.pEngineName = pApp->VkEngineName();

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = extensionCount;
	createInfo.ppEnabledExtensionNames = ppEnableExtensionName;
	createInfo.enabledLayerCount = layerCount;
	createInfo.ppEnabledLayerNames = ppEnableLayerName;

#ifdef _DEBUG
	createInfo.pNext = debugCreateInfo;
#endif // _DEBUG

	VEXCEPT(vkCreateInstance(
		&createInfo, nullptr, &m_vkHandle
	));
	return true;
}

void VulkanWrapper::InstanceHandle::EnumeratePhysicalDevices(
	PhysicalDeviceHandle* outPhys, uint32_t physCount)
{
	vkEnumeratePhysicalDevices(
		m_vkHandle, &physCount, outPhys->VulkanHandleData()
	);
}

uint32_t VulkanWrapper::InstanceHandle::GetPhysicalDeviceCount()
{
	uint32_t dev_count = 0;
	vkEnumeratePhysicalDevices(
		m_vkHandle, &dev_count, nullptr
	);
	return dev_count;
}

void VulkanWrapper::InstanceHandle::Destroy()
{
	vkDestroyInstance(
		m_vkHandle, nullptr
	);
}

VulkanWrapper::Instance::Instance()
{
}

VulkanWrapper::Instance::~Instance()
{
}

bool VulkanWrapper::Instance::Init(
	uint32_t apiVersion,
	IApplication const* pApp,
	char const** ppEnableLayerName,
	uint32_t const layerCount,
	char const** ppEnableExtensionName,
	uint32_t const extensionCount
#ifdef _DEBUG
	, PFN_vkDebugUtilsMessengerCallbackEXT debugCallback
	, void* pUserData
#endif // _DEBUG

)
{
	m_extensions.Clear();
	m_extensions.Resize(extensionCount);
	for (uint32_t i = 0u; i < extensionCount;i++) {
		bool result = m_extensions[i].Copy(ppEnableExtensionName[i]);
		assert(result);
	}
	m_layers.Clear();
	m_layers.Resize(layerCount);
	for (uint32_t i = 0u; i < layerCount; i++) {
		bool result = m_layers[i].Copy(ppEnableLayerName[i]);
		assert(result);
	}
#ifdef _DEBUG
	DebugUtilsMessengerCreateInfo debugCreateInfo(debugCallback, pUserData);
#endif // _DEBUG

	bool result = m_instance.Init(
		apiVersion,
		pApp,
		ppEnableLayerName,
		layerCount,
		ppEnableExtensionName,
		extensionCount
#ifdef _DEBUG
		,&debugCreateInfo
#endif // _DEBUG
	);

	if (!result) return false;
#ifdef _DEBUG
	result = m_debugMessanger.Init(
		m_instance,
		&debugCreateInfo
	);
#endif // _DEBUG
	if (!result) return false;

	uint32_t physCount = m_instance.GetPhysicalDeviceCount();
	m_physDevices.Resize(physCount);
	m_instance.EnumeratePhysicalDevices(
		m_physDevices.Data(),
		physCount
	);

	return true;
}

void VulkanWrapper::Instance::Destroy()
{
#ifdef _DEBUG
	m_debugMessanger.Destroy(m_instance);
#endif // _DEBUG
	m_instance.Destroy();

}

VulkanWrapper::InstanceHandle VulkanWrapper::Instance::GetHandle() const
{
	return m_instance;
}

VulkanWrapper::PhysicalDeviceHandle VulkanWrapper::Instance::GetPhyscalDevice(uint32_t idx)
{
	assert(m_physDevices.Length() > idx);
	return m_physDevices[idx];
}

uint32_t VulkanWrapper::Instance::GetPhysicalDeviceCount()
{
	return m_physDevices.Length();
}

uint32_t VulkanWrapper::Instance::GetLayers(char const** pOutArray, uint32_t buff_size)
{
	assert(buff_size >= m_layers.Length());
	for (uint32_t i = 0; i < m_layers.Length();i++) {
		pOutArray[i] = reinterpret_cast<char const*>(&m_layers[i]);
	}
	return m_layers.Length();
}


uint32_t VulkanWrapper::Instance::GetLayerLength() const
{
	return m_layers.Length();
}


VulkanWrapper::PhysicalDeviceHandle::PhysicalDeviceHandle()
{
}

VulkanWrapper::PhysicalDeviceHandle::~PhysicalDeviceHandle()
{
}

VkPhysicalDeviceProperties VulkanWrapper::PhysicalDeviceHandle::GetProperties() const
{
	VkPhysicalDeviceProperties props;
	vkGetPhysicalDeviceProperties(m_vkHandle, &props);
	return props;
}

VkPhysicalDeviceFeatures VulkanWrapper::PhysicalDeviceHandle::GetFeatures() const
{
	VkPhysicalDeviceFeatures feats;
	vkGetPhysicalDeviceFeatures(m_vkHandle, &feats);
	return feats;
}

void VulkanWrapper::PhysicalDeviceHandle::GetQueueFamilyProperties(VkQueueFamilyProperties* pOutProps, uint32_t count) const
{
	vkGetPhysicalDeviceQueueFamilyProperties(
		m_vkHandle, &count, pOutProps
	);
}

uint32_t VulkanWrapper::PhysicalDeviceHandle::GetQueueFamilyCount() const
{
	uint32_t ret = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(
		m_vkHandle, &ret, nullptr
	);
	return ret;
}
