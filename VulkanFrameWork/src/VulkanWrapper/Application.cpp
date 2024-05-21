#define VK_USE_PLATFORM_WIN32_KHR
#include "VulkanWrapper/Application.h"
#include "VulkanWrapper/Macro.h"
#include "Lib/Container/StaticVector.h"
#include "Lib/Container/Array.h"
#include "Lib/Container/Vector.h"
#include "VulkanWrapper/QueueFamilyIndices.h"
#include "VulkanWrapper/DeviceQueueCreateInfo.h"
#include "VulkanWrapper/SwapChainSupportDetails.h"
#include "Lib/Utility/Logger.h"
#include "Lib/Container/Set.h"
#include <limits> 
#undef max
namespace {
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData) {
		DBG_PRTF("%s\n", pCallbackData->pMessage);

		return VK_FALSE;
	}
}

VulkanWrapper::Application::Application()
{
}

VulkanWrapper::Application::~Application()
{
}

bool VulkanWrapper::Application::Init(HWND _hwnd, HINSTANCE _hinst)
{


	char const* pLayers[] = {
		 "VK_LAYER_KHRONOS_validation"
	};
	char const* pExtensions[] = {
		VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
		VK_KHR_SURFACE_EXTENSION_NAME,
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME
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
	m_surface.Init(
		m_instance.GetHandle(), _hwnd, _hinst
	);

	uint32_t devCount = m_instance.GetPhysicalDeviceCount();
	PhysicalDeviceHandle selectedDevice;
	for (uint32_t i = 0u; i < devCount; i++) {
 		auto physDevice = m_instance.GetPhyscalDevice(i);
		auto prop = physDevice.GetProperties();
		auto feat = physDevice.GetFeatures();
		auto queueFamilyIndices = QueueFamilyIndices(physDevice, m_surface);
		auto swapChainSupport = SwapChainSupportDetails(physDevice, m_surface);
		if (queueFamilyIndices.IsComplete() && swapChainSupport.IsSwapChainSupported()) {
			selectedDevice = physDevice;
			break;
		}
	}


	auto queueFamilyIndices = QueueFamilyIndices(selectedDevice, m_surface);

	VkPhysicalDeviceFeatures feats{};
	Lib::Container::StaticVector<DeviceQueueCreateInfo,2> createInfo{};


	float queuePri = 1.0;
	Lib::Container::Set<uint32_t> indices{};
	queueFamilyIndices.CreateIndexSet(&indices,
		QueueFamilyTypeBit::ALL | QueueFamilyTypeBit::PRESENT_BIT);

	createInfo.Resize(indices.Size());
	uint32_t idx = 0;
	for (auto itr = indices.Begin(); itr != indices.End(); itr++) {
		createInfo[idx].queueFamilyIndex = *itr;
		createInfo[idx].queueCount = 1;
		createInfo[idx].pQueuePriorities = &queuePri;
		idx++;
	}

	char const* pDevExtensions[] = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
	m_device.Init(
		selectedDevice,
		feats,
		createInfo.Data(),
		createInfo.Length(),
		pDevExtensions, _countof(pDevExtensions),
		pLayers, _countof(pLayers)
		);

	m_device.GetQueue(queueFamilyIndices.GetIndex(QueueFamilyType::GRAPHICS), 0, &m_graphicQueue);
	m_device.GetQueue(queueFamilyIndices.GetIndex(QueueFamilyType::PRESENT), 0, &m_presentQueue);

	SwapChainSupportDetails scSupport(m_device.GetPhysicalDevice(), m_surface);
	SurfaceInfo2D scSurfaceInfo{};
	for (auto itr = scSupport.GetFormats().CBegin(); itr != scSupport.GetFormats().CEnd(); ++itr) {
		if (itr->format == VK_FORMAT_B8G8R8A8_SRGB && itr->colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			scSurfaceInfo.Image.Format = itr->format;
			scSurfaceInfo.ColorSpace = itr->colorSpace;
			break;
		}
		scSurfaceInfo.Image.Format = scSupport.GetFormats()[0].format;
		scSurfaceInfo.ColorSpace = scSupport.GetFormats()[0].colorSpace;
	}
	VkPresentModeKHR presentMode;
	for (auto itr = scSupport.GetPresentModes().CBegin(); itr != scSupport.GetPresentModes().CEnd(); ++itr) {
		if (*itr == VK_PRESENT_MODE_MAILBOX_KHR) {
			presentMode = *itr;
			break;
		}
		presentMode = VK_PRESENT_MODE_FIFO_KHR;
	}
	if (scSupport.GetCapablities().currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		scSurfaceInfo.Image.Extent = scSupport.GetCapablities().currentExtent;
	}
	else {
		scSurfaceInfo.Image.Extent.width = GetSystemMetrics(SM_CXSCREEN);
		scSurfaceInfo.Image.Extent.height = GetSystemMetrics(SM_CYSCREEN);
	}
	scSurfaceInfo.Image.Usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	m_swapChain.Init(
		m_device.GetHandle(),
		m_surface,
		presentMode, scSupport.GetCapablities().minImageCount + 1,
		scSurfaceInfo, nullptr, 0,
		scSupport.GetCapablities().currentTransform
	);

	m_vertShader.Init(
		m_device.GetHandle(), "shader/bin/triangle.vert.spirv"
	);
	m_fragShader.Init(
		m_device.GetHandle(), "shader/bin/triangle.frag.spirv"
	);
    return true;
}

void VulkanWrapper::Application::Term()
{
	m_vertShader.Destroy(m_device.GetHandle());
	m_fragShader.Destroy(m_device.GetHandle());
	m_swapChain.Destroy(m_device.GetHandle());
	m_device.Destroy();
	m_surface.Destroy(m_instance.GetHandle());
	m_instance.Destroy();
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
