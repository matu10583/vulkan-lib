#pragma once
#include <vulkan/vulkan.h>
#include "Lib/Container/Vector.h"
#include "Lib/Container/UnqPtr.h"
namespace VulkanWrapper{
	class AttachmentHandle;

class SubpassDescriptionBuilder
{
public:
	SubpassDescriptionBuilder();
	~SubpassDescriptionBuilder();
	SubpassDescriptionBuilder(SubpassDescriptionBuilder&&);
	SubpassDescriptionBuilder& operator=(SubpassDescriptionBuilder&&);
	void ColorAttachments(AttachmentHandle* _pRefs, uint32_t _count,
		AttachmentHandle* _pResolveRefs = nullptr);
	void InputAttachments(AttachmentHandle* _pRefs, uint32_t _count);
	void PreserveAttachments(AttachmentHandle* _pRefs, uint32_t _count);
	void DepthAttachment(AttachmentHandle _pRef);
	VkSubpassDescription Build()const;
private:
	Lib::Container::Vector<VkAttachmentReference> m_colorAttachments;
	Lib::Container::Vector<VkAttachmentReference> m_resolveAttachments;
	Lib::Container::Vector<VkAttachmentReference> m_inputAttachments;
	Lib::Container::Vector<uint32_t> m_preserveAttachments;
	Lib::Container::UnqPtr<VkAttachmentReference> m_deptheAttachment;
};
}
#include "VulkanWrapper/SubpassDescription.inl"