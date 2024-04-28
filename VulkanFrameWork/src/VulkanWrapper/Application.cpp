#include "VulkanWrapper/Application.h"
#include "VulkanWrapper/Macro.h"
#include "Lib/Container/StaticVector.h"
#include "Lib/Container/Array.h"
#include "Lib/Container/Vector.h"
#include "VulkanWrapper/QueueFamilyIndices.h"
#include "VulkanWrapper/DeviceQueueCreateInfo.h"
#include "Lib/Utility/Logger.h"

namespace {
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData) {
		DBG_PRTF("validation layer: %s", pCallbackData->pMessage);

		return VK_FALSE;
	}
}

VulkanWrapper::Application::Application()
{
}

VulkanWrapper::Application::~Application()
{
}

bool VulkanWrapper::Application::Init()
{
	char const* pLayers[] = {
		 "VK_LAYER_KHRONOS_validation"
	};
	char const* pExtensions[] = {
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME
	};
	m_instance.Init(
		VK_API_VERSION_1_0,
		this,
		pLayers, _countof(pLayers),
		pExtensions,_countof(pExtensions)
#ifdef _DEBUG
		,debugCallback
#endif // _DEBUG

	);
	uint32_t devCount = m_instance.GetPhysicalDeviceCount();
	PhysicalDeviceHandle selectedDevice;
	for (uint32_t i = 0u; i < devCount; i++) {
 		auto physDevice = m_instance.GetPhyscalDevice(i);
		auto prop = physDevice.GetProperties();
		auto feat = physDevice.GetFeatures();
		selectedDevice = physDevice;
		break;
	}
	VkPhysicalDeviceFeatures feats{};
	Lib::Container::Array<DeviceQueueCreateInfo, 1> createInfo{};

	auto queueFamilyIndices = QueueFamilyIndices(selectedDevice);
	createInfo[0].queueFamilyIndex = queueFamilyIndices.GetIndex(QueueFamilyType::GRAPHICS);
	createInfo[0].queueCount = 1;
	float queuePri = 1.0;
	createInfo[0].pQueuePriorities = &queuePri;

	m_device.Init(
		selectedDevice,
		feats,
		createInfo.Data(),
		createInfo.Length(),
		nullptr, 0,
		pLayers, _countof(pLayers)
		);

    return true;
}

uint32_t VulkanWrapper::Application::VkAppVersion() const
{
	return VK_MAKE_VERSION(1, 0, 0);
}

uint32_t VulkanWrapper::Application::VkEngineVersion() const
{
    return VK_MAKE_VERSION(1, 0, 0);
}

char const* VulkanWrapper::Application::VkApplicationName() const
{
    return "Hello World";
}

char const* VulkanWrapper::Application::VkEngineName() const
{
    return "No Engine";
}
