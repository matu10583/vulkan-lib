#include "VulkanWrapper/Queue.h"
namespace VulkanWrapper{
        QueueHandle::~QueueHandle(){

        }
        QueueHandle::QueueHandle()
        :VulkanWrapper::VulkanHandleBase<VkQueue>()
        {
        }


        Queue::Queue()
        {
        }

        Queue::~Queue()
        {
        }
}
