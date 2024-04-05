#include "VulkanWrapper/Instance.h"
#include "VulkanWrapper/IApplication.h"
#include "VulkanWrapper/Macro.h"
VulkanWrapper::InstanceHandle::InstanceHandle()
	:m_vkInstance(VK_NULL_HANDLE)
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

	VEXCEPT(vkCreateInstance(
		&createInfo, nullptr, &m_vkInstance
	));
	return true;
}

void VulkanWrapper::InstanceHandle::Destroy()
{
	vkDestroyInstance(
		m_vkInstance, nullptr
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
	uint32_t const extensionCount)
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
	return m_instance.Init(
		apiVersion,
		pApp,
		ppEnableLayerName,
		layerCount,
		ppEnableExtensionName,
		extensionCount
	);
}

void VulkanWrapper::Instance::Destroy()
{
	m_instance.Destroy();
}

VulkanWrapper::InstanceHandle VulkanWrapper::Instance::GetHandle() const
{
	return m_instance;
}
