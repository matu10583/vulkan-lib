#pragma once
#include "VulkanWrapper/IApplication.h"
#include "VulkanWrapper/Instance.h"
#include "VulkanWrapper/Device.h"

namespace VulkanWrapper {
	class Application 
		: public IApplication
	{
	public:
		Application();
		~Application();
		bool Init();

		// IApplication ����Čp������܂���
		uint32_t VkAppVersion() const override;

		uint32_t VkEngineVersion() const override;

		char const* VkApplicationName() const override;

		char const* VkEngineName() const override;

	private:
		Instance m_instance;
		Device m_device;
	};
}


