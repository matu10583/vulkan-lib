#include "VulkanWrapper/Queue.h"
#include "VulkanWrapper/Fence.h"
#include "VulkanWrapper/Macro.h"
namespace VulkanWrapper{
        QueueHandle::~QueueHandle(){

        }
        void QueueHandle::Submit(uint32_t _submitInfoCount, VkSubmitInfo * _pSubmitInfos, FenceHandle _signalFence)
        {
            VEXCEPT(
                vkQueueSubmit(
                    m_vkHandle, _submitInfoCount, _pSubmitInfos,
                    _signalFence
                )
            );
        }
        void QueueHandle::Present(VkPresentInfoKHR* _presentInfo)
        {
            _presentInfo->pResults = nullptr;
#ifdef _DEBUG
            _presentInfo->pResults = 
                new VkResult[_presentInfo->swapchainCount];
#endif // _DEBUG
            VEXCEPT(
                vkQueuePresentKHR(
                    m_vkHandle, _presentInfo
                )
            );
#ifdef _DEBUG
            for (uint32_t i = 0; i < _presentInfo->swapchainCount; i++) {
                VEXCEPT(_presentInfo->pResults[i]);
            }
#endif // _DEBUG


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
        void Queue::Submit(uint32_t _submitInfoCount, VkSubmitInfo * _pSubmitInfos, FenceHandle _signalFence)
        {
            m_queue.Submit(
                _submitInfoCount, _pSubmitInfos, _signalFence
            );
        }
        void Queue::Present(VkPresentInfoKHR* _presentInfo)
        {
            m_queue.Present(_presentInfo);
        }
}
