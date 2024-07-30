#include "VulkanWrapper/SubpassDescription.h"
#include "Lib/Utility/Macro.h"
#include "Lib/Container/Generator.h"
#include "VulkanWrapper/RenderPassCreateInfo.h"

namespace VulkanWrapper {
    SubpassDescriptionBuilder::SubpassDescriptionBuilder()
    {
    }
    SubpassDescriptionBuilder::~SubpassDescriptionBuilder()
    {
    }
    SubpassDescriptionBuilder::SubpassDescriptionBuilder(SubpassDescriptionBuilder&& _v)
        :m_colorAttachments(std::move(_v.m_colorAttachments))
        , m_resolveAttachments(std::move(_v.m_resolveAttachments))
        , m_inputAttachments(std::move(_v.m_inputAttachments))
        , m_preserveAttachments(std::move(_v.m_preserveAttachments))
        , m_deptheAttachment(std::move(_v.m_deptheAttachment))
    {
    }
    SubpassDescriptionBuilder& SubpassDescriptionBuilder::operator=(SubpassDescriptionBuilder&& _v)
    {
        m_colorAttachments = std::move(_v.m_colorAttachments);
        m_resolveAttachments = std::move(_v.m_resolveAttachments);
        m_inputAttachments = std::move(_v.m_inputAttachments);
        m_preserveAttachments = std::move(_v.m_preserveAttachments);
        m_deptheAttachment = std::move(_v.m_deptheAttachment);
        return *this;
        // TODO: return ステートメントをここに挿入します
    }
    void SubpassDescriptionBuilder::ColorAttachments(AttachmentHandle* _pRefs, uint32_t _count, AttachmentHandle* _pResolveRefs)
    {
        m_colorAttachments = Lib::Container::MakeRange(_pRefs, _count)
            .Select([](AttachmentHandle const& _h, int32_t i) {
            return _h.GetRef();
                }).ToVector();
        if (_pResolveRefs == nullptr)return;
        m_resolveAttachments = Lib::Container::MakeRange(_pResolveRefs, _count)
            .Select([](AttachmentHandle const& _h) {
            return _h.GetRef();
                }).ToVector();
    }
    void SubpassDescriptionBuilder::InputAttachments(AttachmentHandle* _pRefs, uint32_t _count)
    {
        m_inputAttachments = Lib::Container::MakeRange(_pRefs, _count)
            .Select([](AttachmentHandle const& _h) {
            return _h.GetRef();
                }).ToVector();
    }
    void SubpassDescriptionBuilder::PreserveAttachments(AttachmentHandle* _pRefs, uint32_t _count)
    {
        m_preserveAttachments = Lib::Container::MakeRange(_pRefs, _count)
            .Select([](AttachmentHandle const& _h) {
            return _h.GetRef().attachment;
                }).ToVector();
    }
    void SubpassDescriptionBuilder::DepthAttachment(AttachmentHandle _pRef)
    {
        m_deptheAttachment = Lib::Container::MakeUnique<VkAttachmentReference>();
        *m_deptheAttachment = _pRef.GetRef();
    }
    VkSubpassDescription SubpassDescriptionBuilder::Build() const
    {
        VkSubpassDescription ret{};
        ret.flags = 0;
        ret.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        ret.inputAttachmentCount = m_inputAttachments.Length();
        ret.pInputAttachments = (ret.inputAttachmentCount == 0) ? nullptr : m_inputAttachments.Data();
        ret.colorAttachmentCount = m_colorAttachments.Length();
        ret.pColorAttachments = (ret.colorAttachmentCount == 0) ? nullptr : m_colorAttachments.Data();
        ret.pResolveAttachments = (m_resolveAttachments.Length() == 0) ? nullptr : m_resolveAttachments.Data();
        ret.preserveAttachmentCount = m_preserveAttachments.Length();
        ret.pPreserveAttachments = (ret.preserveAttachmentCount == 0) ? nullptr : m_preserveAttachments.Data();
        return ret;
    }
}
