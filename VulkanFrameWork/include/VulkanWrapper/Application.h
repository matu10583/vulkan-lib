#pragma once
#include "VulkanWrapper/IApplication.h"
#include "VulkanWrapper/Instance.h"
#include "VulkanWrapper/Device.h"
#include "VulkanWrapper/Queue.h"
#include "VulkanWrapper/Surface.h"
#include "VulkanWrapper/SwapChain.h"
#include "VulkanWrapper/ShaderModule.h"
#include "VulkanWrapper/GraphicsPipeline.h"
#include "VulkanWrapper/RenderPass.h"
#include "VulkanWrapper/PipelineLayout.h"
#include "VulkanWrapper/GraphicsPipeline.h"
#include "VulkanWrapper/FrameBuffer.h"
#include "Lib/Container/Vector.h"
#include "VulkanWrapper/CommandPool.h"
#include "VulkanWrapper/CommandBuffer.h"
#include "VulkanWrapper/QueueFamilyIndices.h"
#include "VulkanWrapper/Semahore.h"
#include "VulkanWrapper/Fence.h"

namespace VulkanWrapper {
	class SubpassHandle;
	class Application 
		: public IApplication
	{
	public:
		Application();
		~Application();
		bool Init(HWND _hwnd, HINSTANCE _hinst);
		void Term();
		void Update();

		// IApplication ÇâÓÇµÇƒåpè≥Ç≥ÇÍÇ‹ÇµÇΩ
		uint32_t VkAppVersion() const override;

		uint32_t VkEngineVersion() const override;

		char const* VkApplicationName() const override;

		char const* VkEngineName() const override;

	private:
		void Draw();
		void RecordBuffer(uint32_t _idx);
		void SubmitQueue(uint32_t _imageIdx);
		bool InitPipeline(
		SubpassHandle _handle);
		bool InitFrameBuffers();
		bool InitCommandBuffer();
		void InitSyncObject();

		Instance m_instance;
		Device m_device;
		Queue m_graphicQueue;
		Queue m_presentQueue;
		SurfaceHandle m_surface;
		SwapChain m_swapChain;
		ShaderModuleHandle m_vertShader;
		ShaderModuleHandle m_fragShader;
		RenderPassHandle m_renderPass;
		PipelineLayoutHandle m_pipelineLayout;
		GrapchicsPipelineHandle m_pipeline;
		Lib::Container::Vector<FrameBufferHandle> m_frameBuffers;
		QueueFamilyIndices m_queueIndices;
		CommandPoolHandle m_graphicCommandPool;
		void initPipelineState();
		CommandBufferHandle m_graphicCommandBuffer;
		SemaphoreHandle m_imageAvailableSemaphore;
		SemaphoreHandle m_renderFinishedSemaphore;
		FenceHandle m_inFlightFence;

	};
}


