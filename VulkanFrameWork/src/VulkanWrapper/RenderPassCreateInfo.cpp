#include "VulkanWrapper/RenderPassCreateInfo.h"
#include <cassert>
#include "Lib/Utility/Macro.h"
namespace VulkanWrapper{
    RenderPassCreateInfoBuilder::RenderPassCreateInfoBuilder()
    {

    }
    RenderPassCreateInfoBuilder::~RenderPassCreateInfoBuilder()
    {

    }
    AttachmentHandle RenderPassCreateInfoBuilder::AddColorAttachment()
    {
        uint32_t id = m_attachmentDescriptions.Add(
            VkAttachmentDescription()
        );
        return AttachmentHandle(id, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, this);
    }
    SubpassHandle RenderPassCreateInfoBuilder::AddSubpass()
    {
        uint32_t id = m_subpassBuilders.Add(
            SubpassDescriptionBuilder()
        );
        return SubpassHandle(id, this);
    }

    RenderPassCreateInfoBuilder& RenderPassCreateInfoBuilder::AddDependency(SubpassHandle _srcSubpass, VkPipelineStageFlags _srcStageMasks, VkAccessFlags _scrAccessFlags, SubpassHandle _dstSubpass, VkPipelineStageFlags _dstStageMasks, VkAccessFlags _dstAccessFlags)
    {
        m_subpassDependencies.EmplaceBack(
            VkSubpassDependency()
        );
        auto& dependency = m_subpassDependencies.Back();
        dependency.srcSubpass = _srcSubpass.GetSubpassIndex();
        dependency.srcStageMask = _srcStageMasks;
        dependency.srcAccessMask = _scrAccessFlags;
        
        dependency.dstSubpass = _dstSubpass.GetSubpassIndex();
        dependency.dstStageMask = _dstStageMasks;
        dependency.dstAccessMask = _dstAccessFlags;
        return *this;
        // TODO: return ステートメントをここに挿入します
    }


    VkRenderPassCreateInfo RenderPassCreateInfoBuilder::Build() 
    {
        //寿命があるとしたらこいつと一緒にしたいので保持
        m_subpasses = m_subpassBuilders.GetEnumerator()
            .Select([](SubpassDescriptionBuilder const& _builder) {
            return _builder.Build();
                }).ToVector();
        VkRenderPassCreateInfo ret{};
        ret.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        ret.pNext = nullptr;
        ret.flags = 0;
        ret.attachmentCount = m_attachmentDescriptions.Length();
        ret.pAttachments = (m_attachmentDescriptions.Length()==0)?nullptr:m_attachmentDescriptions.Data();
        ret.subpassCount = m_subpasses.Length();
        ret.pSubpasses = (m_subpasses.Length()==0)?nullptr:m_subpasses.Data();
        ret.dependencyCount = m_subpassDependencies.Length();
        ret.pDependencies = (m_subpassDependencies.Length() == 0) ? nullptr: m_subpassDependencies.Data();
        return ret;
    }
    VkAttachmentDescription* RenderPassCreateInfoBuilder::GetAttachmentDescription(AttachmentHandle _handle)
    {
        return m_attachmentDescriptions.Get(_handle.GetRef().attachment);
    }

    uint32_t RenderPassCreateInfoBuilder::GetAttachmentIdx(AttachmentHandle _handle) const
    {
        return m_attachmentDescriptions.GetIdx(_handle.GetId());
    }

    SubpassDescriptionBuilder* RenderPassCreateInfoBuilder::GetSubpassDescription(SubpassHandle _handle)
    {
        return m_subpassBuilders.Get(_handle.GetId());
    }

    uint32_t RenderPassCreateInfoBuilder::GetSubpassIdx(SubpassHandle _handle) const
    {
        return m_subpassBuilders.GetIdx(_handle.GetId());
    }

}
