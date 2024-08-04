#include "VulkanWrapper/RenderPassBeginInfo.h"
#include <string>
#include "Lib/Utility/Macro.h"
#include "VulkanWrapper/RenderPass.h"
#include "VulkanWrapper/FrameBuffer.h"
namespace VulkanWrapper{
    RenderPassBeginInfo::RenderPassBeginInfo(RenderPassHandle _renderPass, FrameBufferHandle _frameBuffer)
        :VkRenderPassBeginInfo()
    {
        this->sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        this->clearValueCount = 0;
        this->framebuffer = _frameBuffer.GetVulkanHandle();
        this->pClearValues = nullptr;
        this->renderPass = _renderPass;
    }
    RenderPassBeginInfo& RenderPassBeginInfo::SetArea(VkOffset2D _offset, VkExtent2D _extent)
    {
        renderArea.extent = _extent;
        renderArea.offset = _offset;
        return *this;
        // TODO: return ステートメントをここに挿入します
    }
    RenderPassBeginInfo& RenderPassBeginInfo::SetClearValues(uint32_t _clearValueCount, float const** _color, float const* _depth, uint32_t const* _stencil)
    {
        m_clearValues.Resize(_clearValueCount);
        uint32_t count = 0;
        foreach(cv, m_clearValues) {
            if (_color[count]) {
                memcpy_s(cv->color.float32,
                    sizeof(float) * 4, _color[count],
                    sizeof(float) * 4);
            }
            if (_depth && _depth[count]) {
                cv->depthStencil.depth = _depth[count];
            }
            if (_stencil && _stencil[count]) {
                cv->depthStencil.stencil = _stencil[count];
            }
            count++;
        }
        this->clearValueCount = m_clearValues.Length();
        this->pClearValues = m_clearValues.Data();
        return *this;
        // TODO: return ステートメントをここに挿入します
    }
}
