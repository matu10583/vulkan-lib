#include "VulkanWrapper/PresentInfo.h"
#include "VulkanWrapper/Semahore.h"
#include "VulkanWrapper/SwapChain.h"

namespace VulkanWrapper{
    PresentInfo::PresentInfo()
        :VkPresentInfoKHR()
    {
        sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        pResults = nullptr;
    }

    PresentInfo& PresentInfo::WaitSemaphore(uint32_t _semaphoreCount, SemaphoreHandle* _pSemaphores)
    {
        waitSemaphoreCount = _semaphoreCount;
        pWaitSemaphores = _pSemaphores->VulkanHandleData();
        return *this;
        // TODO: return ステートメントをここに挿入します
    }

    PresentInfo& PresentInfo::SwapChainImages(uint32_t _scCount, SwapChainHandle* _scHandles, uint32_t* _pImageIndices)
    {
        swapchainCount = _scCount;
        pSwapchains = _scHandles->VulkanHandleData();
        pImageIndices = _pImageIndices;
        return *this;
        // TODO: return ステートメントをここに挿入します
    }

}
