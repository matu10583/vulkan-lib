#define VK_USE_PLATFORM_WIN32_KHR
#include "VulkanWrapper/Application.h"
#include "VulkanWrapper/Macro.h"
#include "Lib/Container/StaticVector.h"
#include "Lib/Container/Array.h"
#include "Lib/Container/Vector.h"
#include "Lib/Utility/Logger.h"
#include "Lib/Container/Set.h"
#include <limits> 
#include "Lib/Container/Generator.h"
#include "Lib/Utility/Macro.h"
#include "VulkanWrapper/Functions.h"
#include "VulkanWrapper/CreateInfos.h"
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
		auto queueFamilyIndices = QueueFamilyIndices();
		queueFamilyIndices.Init(physDevice, m_surface);
		auto swapChainSupport = SwapChainSupportDetails(physDevice, m_surface);
		if (queueFamilyIndices.IsComplete() && swapChainSupport.IsSwapChainSupported()) {
			selectedDevice = physDevice;
			break;
		}
	}


	m_queueIndices.Init(selectedDevice, m_surface);

	VkPhysicalDeviceFeatures feats{};
	Lib::Container::StaticVector<DeviceQueueCreateInfo, 2> createInfo{};


	float queuePri = 1.0;
	Lib::Container::Set<uint32_t> indices{};
	m_queueIndices.CreateIndexSet(&indices,
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

	m_device.GetQueue(m_queueIndices.GetIndex(QueueFamilyType::GRAPHICS), 0, &m_graphicQueue);
	m_device.GetQueue(m_queueIndices.GetIndex(QueueFamilyType::PRESENT), 0, &m_presentQueue);

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

	////òAë≈sÅ|ÉpÉX
	RenderPassCreateInfoBuilder rpciBuilder{};
	Lib::Container::StaticVector<AttachmentHandle, 1> attachments{};
	attachments.EmplaceBack(
		rpciBuilder.AddColorAttachment()
	);
	attachments[0]
		.Format(m_swapChain.GetFormat())
		.LoadOp(VK_ATTACHMENT_LOAD_OP_CLEAR)
		.StoreOp(VK_ATTACHMENT_STORE_OP_STORE)
		.InitialLayout(VK_IMAGE_LAYOUT_UNDEFINED)
		.FinalLayout(VK_IMAGE_LAYOUT_PRESENT_SRC_KHR)
		.Samples(VK_SAMPLE_COUNT_1_BIT);
	

	Lib::Container::StaticVector<SubpassHandle, 1> subpasses{};
	subpasses.EmplaceBack(rpciBuilder.AddSubpass());
	subpasses[0]
		.ColorAttachments(
			attachments.Data(), attachments.Length()
		);
	rpciBuilder.AddDependency(
		{},
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		0,
		subpasses[0],
		VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT
	);
	
	auto rpCreateInfo = rpciBuilder.Build();
	m_renderPass.Init(rpCreateInfo, m_device.GetHandle());
	InitPipeline(subpasses[0]);
    return true;
}

void VulkanWrapper::Application::Term()
{
	m_device.WaitIdle();
	m_inFlightFence.Destroy(m_device.GetHandle());
	m_renderFinishedSemaphore.Destroy(m_device.GetHandle());
	m_imageAvailableSemaphore.Destroy(m_device.GetHandle());
	m_graphicCommandPool.Destroy(m_device.GetHandle());
	foreach(fb, m_frameBuffers) {
		fb->Destroy(m_device.GetHandle());
	}
	m_pipeline.Destroy(m_device.GetHandle());
	m_pipelineLayout.Destroy(m_device.GetHandle());
	m_renderPass.Destroy(m_device.GetHandle());
	m_vertShader.Destroy(m_device.GetHandle());
	m_fragShader.Destroy(m_device.GetHandle());
	m_swapChain.Destroy(m_device.GetHandle());
	m_device.Destroy();
	m_surface.Destroy(m_instance.GetHandle());
	m_instance.Destroy();
}

void VulkanWrapper::Application::Update()
{
	Draw();
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

void VulkanWrapper::Application::Draw()
{
	m_device.WaitIdle();
	vkWaitForFences(
		m_device.GetHandle().GetVulkanHandle(), 1,
		m_inFlightFence.VulkanHandleData(), VK_TRUE,
		UINT64_MAX
	);
	vkResetFences(
		m_device.GetHandle().GetVulkanHandle(),
		1, m_inFlightFence.VulkanHandleData()
	);
	uint32_t imgIdx = m_swapChain.AcquireNextImageIndex(
		m_device.GetHandle(), UINT64_MAX, m_imageAvailableSemaphore, {}
	);
	m_graphicCommandBuffer.Reset(0);
	RecordBuffer(imgIdx);
	SubmitQueue(imgIdx);
}

void VulkanWrapper::Application::RecordBuffer(uint32_t _idx)
{
	auto begin = CommandBufferBeginInfo();
	m_graphicCommandBuffer.CmdBegin(&begin);
	auto rpbegin = RenderPassBeginInfo(
		m_renderPass, m_frameBuffers[_idx]
	);
	auto swapChainExtent = m_swapChain.GetExtent2D();
	auto offset = VkOffset2D();
	offset.x = offset.y = 0;
	rpbegin.SetArea(
		offset, swapChainExtent
	);
	float pcolors[] = {
		0.0f, 0.0f, 0.0f, 1.0f
	};
	float const* ppcol[] = { pcolors };
	rpbegin.SetClearValues(
		1, ((float const**)ppcol)
	);
	m_graphicCommandBuffer.CmdBeginRenderPass(&rpbegin, VK_SUBPASS_CONTENTS_INLINE);
	m_graphicCommandBuffer.CmdBindGraphicPipeline(
		m_pipeline
	);
	auto viewport = VkViewport();
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = static_cast<float>(swapChainExtent.width);
	viewport.height = static_cast<float>(swapChainExtent.height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	m_graphicCommandBuffer.CmdSetViewPort(&viewport, 1);
	VkRect2D scissor{};
	scissor.offset = { 0, 0 };
	scissor.extent = swapChainExtent;
	m_graphicCommandBuffer.CmdSetScissor(&scissor, 1);
	m_graphicCommandBuffer.CmdDraw(3, 1, 0, 0);
	m_graphicCommandBuffer.CmdEndRenderPass();
	m_graphicCommandBuffer.CmdEnd();


}

void VulkanWrapper::Application::SubmitQueue(uint32_t _imageIdx)
{
	auto submitInfo = SubmitInfo();
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.CommandBuffer(
		1, &m_graphicCommandBuffer
	)
		.WaitSemaphore(
			1, &m_imageAvailableSemaphore,
			waitStages
		)
		.SignalSemaphore(
			1, &m_renderFinishedSemaphore
		);
	m_graphicQueue.Submit(
		1, &submitInfo, m_inFlightFence);

	auto presentInfo = PresentInfo();
	uint32_t imageIndices[] = {_imageIdx};
	SwapChainHandle swapchains[] = {m_swapChain.GetSwapChain()};
	presentInfo.SwapChainImages(
		1, swapchains, imageIndices
	);
	SemaphoreHandle semaphores[] = {
		m_renderFinishedSemaphore
	};
	presentInfo.WaitSemaphore(
		_countof(semaphores), semaphores
	);
	m_presentQueue.Present(&presentInfo);
}

bool VulkanWrapper::Application::InitPipeline(
	SubpassHandle _subpass
)
{
	m_pipelineLayout.Init(m_device.GetHandle());

	VkDynamicState dss[] = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};
	auto dynamicState = PipelineDynamicStateCreateInfo(
		&dss[0], _countof(dss)
	);
	auto vertexInput = PipelineVertexInputStateCreateInfo(
		nullptr, 0,
		nullptr, 0
	);
	auto inputAssembly = PipelineInputAssemblyStateCreateInfo(
		VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST
	);
	auto rasterizationState = PipelineRasterizationStateCreateInfo(
		VK_FRONT_FACE_CLOCKWISE
	);

	auto multiSampling = PipelineMultisampleStateCreateInfo();

	auto colorBlendingAttachment = PipelineColorBlendAttachmentState();

	auto colorBlending = PipelineColorBlendStateCreateInfo(
		&colorBlendingAttachment, 1
	);

	auto viewport = PipelineViewportStateCreateInfo(
		nullptr, 1, nullptr, 1
	);

	PipelineShaderStageCreateInfo shaderStage[2];
	shaderStage[0].SetShader(
		m_vertShader, "main", VK_SHADER_STAGE_VERTEX_BIT
	);
	shaderStage[1].SetShader(
		m_fragShader, "main", VK_SHADER_STAGE_FRAGMENT_BIT
	);


	auto createInfo = GraphicsPipelineCreateInfo();
	createInfo.ColorBlendState(&colorBlending)
		.DepthStencilState(nullptr)
		.DynamicState(&dynamicState)
		.InputAssemblyState(&inputAssembly)
		.MultisampleState(&multiSampling)
		.PipelineLayout(m_pipelineLayout)
		.RasterizationStatetexInputState(&rasterizationState)
		.RenderPass(m_renderPass, _subpass.GetSubpassIndex())
		.ShaderStages(&shaderStage[0], _countof(shaderStage))
		.VertexInputState(&vertexInput)
		.ViewportState(&viewport);

	m_pipeline.Init(
		m_device.GetHandle(),
		&createInfo
	);
	InitFrameBuffers();
	InitCommandBuffer();
	InitSyncObject();
	return true;
}

bool VulkanWrapper::Application::InitFrameBuffers()
{
	m_frameBuffers.Resize(m_swapChain.GetImageCount());
	auto fbs = m_frameBuffers.GetEnumerator();
	while (fbs.MoveNext())
	{
		ImageViewHandle views[] = {
			m_swapChain.GetImageHandle(fbs.CurrentIndex())
		};
		FrameBufferCreateInfo createInfo(
			m_renderPass, views, _countof(views),
			m_swapChain.GetExtent2D(), 1
		);
		fbs.Current().Init(
			m_device.GetHandle(), createInfo
		);
	}

	return true;
}

bool VulkanWrapper::Application::InitCommandBuffer()
{
	auto createInfo = CommandPoolCreateInfo(
		m_queueIndices.GetIndex(QueueFamilyType::GRAPHICS),
		VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT
	);
	m_graphicCommandPool.Init(
		m_device.GetHandle(), createInfo
	);
	auto allocateInfo = CommandBufferAllocateInfo(
		m_graphicCommandPool,
		VK_COMMAND_BUFFER_LEVEL_PRIMARY, 1
	);
	AllocateCommandBuffer(
		m_device.GetHandle(),
		allocateInfo,
		&m_graphicCommandBuffer
	);

	return true;
}

void VulkanWrapper::Application::InitSyncObject()
{
	auto imgSemCreateInfo = SemaphoreCreateInfo();
	m_imageAvailableSemaphore.Init(
		m_device.GetHandle(), &imgSemCreateInfo
	);
	auto renSemCreateInfo = SemaphoreCreateInfo();
	m_renderFinishedSemaphore.Init(
		m_device.GetHandle(), &renSemCreateInfo
	);
	auto infFenceCreateInfo = FenceCreateInfo(VK_FENCE_CREATE_SIGNALED_BIT);
	m_inFlightFence.Init(
		m_device.GetHandle(),
		&infFenceCreateInfo
	);
}

void VulkanWrapper::Application::initPipelineState()
{
	VkDynamicState dss[] = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR
	};
	auto dynamicState = PipelineDynamicStateCreateInfo(dss, _countof(dss));

}
