#pragma once
#include "VulkanWrapper/VulkanHandleBase.h"
namespace VulkanWrapper{
class QueueHandle
:
public VulkanWrapper::VulkanHandleBase<VkQueue>
{
public:
        QueueHandle();
        ~QueueHandle();
};

class Queue
{
	friend class Device;
public:
	Queue();
	~Queue();
private:
	QueueHandle m_queue;;
};


}
