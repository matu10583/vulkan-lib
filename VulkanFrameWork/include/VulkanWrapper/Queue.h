#pragma once
#include "VulkanWrapper/VulkanHandleBase.h"
namespace VulkanWrapper{
	class FenceHandle;
class QueueHandle
:
public VulkanWrapper::VulkanHandleBase<VkQueue>
{
public:
        QueueHandle();
        ~QueueHandle();
		void Submit(
			uint32_t _submitInfoCount, VkSubmitInfo * _pSubmitInfos,
			FenceHandle _signalFence
		);
		void Present(
			VkPresentInfoKHR* _presentInfo
		);
};

class Queue
{
	friend class Device;
public:
	Queue();
	~Queue();
	void Submit(
		uint32_t _submitInfoCount, VkSubmitInfo * _pSubmitInfos,
		FenceHandle _signalFence
	);
	void Present(
		VkPresentInfoKHR* _presentInfo
	);
private:
	QueueHandle m_queue;;
};


}
