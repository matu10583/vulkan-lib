#pragma once
#include <cassert>
#include "RenderPassCreateInfo.h"
namespace VulkanWrapper{
    inline VkAttachmentReference AttachmentHandle::GetRef() const
    {
        VkAttachmentReference ret{};
        ret.attachment = m_pParent->GetAttachmentIdx(*this);
        ret.layout = m_layout;
        return ret;
    }
    inline uint32_t AttachmentHandle::GetId() const
    {
        return m_sparseId;
    }
    inline AttachmentHandle& AttachmentHandle::Format(VkFormat _format)
    {
        auto* desc = m_pParent->GetAttachmentDescription(*this);
        assert(desc != nullptr);
        desc->format = _format;
        return *this;
    }
    inline AttachmentHandle& AttachmentHandle::LoadOp(VkAttachmentLoadOp _op, VkAttachmentLoadOp _stencil)
    {
        auto* desc = m_pParent->GetAttachmentDescription(*this);
        assert(desc != nullptr);
        desc->loadOp = _op;
        desc->stencilLoadOp = _stencil;
        return *this;
    }
    inline AttachmentHandle& AttachmentHandle::StoreOp(VkAttachmentStoreOp _op, VkAttachmentStoreOp _stencil)
    {
        auto* desc = m_pParent->GetAttachmentDescription(*this);
        assert(desc != nullptr);
        desc->storeOp = _op;
        desc->stencilStoreOp = _stencil;
        return *this;
    }
    inline AttachmentHandle& AttachmentHandle::InitialLayout(VkImageLayout _layout)
    {
        auto* desc = m_pParent->GetAttachmentDescription(*this);
        assert(desc != nullptr);
        desc->initialLayout = _layout;
        return *this;
    }
    inline AttachmentHandle& AttachmentHandle::FinalLayout(VkImageLayout _layout)
    {
        auto* desc = m_pParent->GetAttachmentDescription(*this);
        assert(desc != nullptr);
        desc->finalLayout = _layout;
        return *this;
    }
    inline AttachmentHandle& AttachmentHandle::Samples(VkSampleCountFlagBits _samples)
    {
        auto* desc = m_pParent->GetAttachmentDescription(*this);
        assert(desc != nullptr);
        desc->samples = _samples;
        return *this;
    }
    inline uint32_t SubpassHandle::GetSubpassIndex() const
    {
        if (m_sparseId == UINT32_MAX) return VK_SUBPASS_EXTERNAL;
        return m_pParent->GetSubpassIdx(*this);
    }
    inline uint32_t SubpassHandle::GetId() const
    {
        return m_sparseId;
    }
    //TODO: 内部の処理変える。Handleのポインタを受け取ってそこからSelectでReferenceの配列を作る。
    //そのためにRangeオブジェクトをEnumeratorとして作る。ハンドルのまま運んでBuilderに渡した方がいいな.コピーが減る
    inline SubpassHandle& SubpassHandle::InputAttachments(AttachmentHandle* _pRefs, uint32_t _count)
    {
        auto* desc = m_pParent->GetSubpassDescription(*this);
        desc->InputAttachments(_pRefs, _count);
        return *this;
        // TODO: return ステートメントをここに挿入します
    }
    inline SubpassHandle& SubpassHandle::ColorAttachments(AttachmentHandle* _pRefs, uint32_t _count,
        AttachmentHandle* _pResolveRefs)
    {
        auto* desc = m_pParent->GetSubpassDescription(*this);
        desc->ColorAttachments(
            _pRefs, _count, _pResolveRefs
        );
        return *this;
        // TODO: return ステートメントをここに挿入します
    }
    inline SubpassHandle& SubpassHandle::PreserveAttachments(AttachmentHandle* _pRefs, uint32_t _count)
    {
        auto* desc = m_pParent->GetSubpassDescription(*this);
        desc->PreserveAttachments(_pRefs, _count);
        return *this;
        // TODO: return ステートメントをここに挿入します
    }
    inline SubpassHandle& SubpassHandle::DepthAttachment(AttachmentHandle _Ref)
    {
        auto* desc = m_pParent->GetSubpassDescription(*this);
        desc->DepthAttachment(_Ref);
        return *this;
        // TODO: return ステートメントをここに挿入します
    }
}
