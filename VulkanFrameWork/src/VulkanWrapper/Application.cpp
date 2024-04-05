#include "VulkanWrapper/Application.h"
#include "VulkanWrapper/Macro.h"

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
	//char const* pExtensions[] = {
	//};
	m_instance.Init(
		VK_API_VERSION_1_0,
		this,
		pLayers, _countof(pLayers),
		nullptr,0
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
