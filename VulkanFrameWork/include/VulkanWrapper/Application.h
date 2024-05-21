#pragma once
#include "VulkanWrapper/IApplication.h"
#include "VulkanWrapper/Instance.h"
#include "VulkanWrapper/Device.h"
#include "VulkanWrapper/Queue.h"
#include "VulkanWrapper/Surface.h"
#include "VulkanWrapper/SwapChain.h"
#include "VulkanWrapper/ShaderModule.h"

namespace VulkanWrapper {
	class Application 
		: public IApplication
	{
	public:
		Application();
		~Application();
		bool Init(HWND _hwnd, HINSTANCE _hinst);
		void Term();

		// IApplication ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
		uint32_t VkAppVersion() const override;

		uint32_t VkEngineVersion() const override;

		char const* VkApplicationName() const override;

		char const* VkEngineName() const override;

	private:
		Instance m_instance;
		Device m_device;
		Queue m_graphicQueue;
		Queue m_presentQueue;
		SurfaceHandle m_surface;
		SwapChain m_swapChain;
		ShaderModuleHandle m_vertShader;
		ShaderModuleHandle m_fragShader;
	};
}


