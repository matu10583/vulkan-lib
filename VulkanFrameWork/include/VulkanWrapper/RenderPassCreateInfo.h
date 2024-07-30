#pragma once
#include <vulkan/vulkan.h>
#include "Lib/Container/Vector.h"
#include "Lib/Container/SparseVector.h"
#include "VulkanWrapper/SubpassDescription.h"
namespace VulkanWrapper{
	class RenderPassCreateInfoBuilder;

	class AttachmentHandle
	{
	public:
		AttachmentHandle(uint32_t idx, VkImageLayout _layout, RenderPassCreateInfoBuilder* _parent)
		{
			m_sparseId = idx;
			m_layout = _layout;
			m_pParent = _parent;
		}
		AttachmentHandle()
		{
			m_sparseId = UINT32_MAX;
			m_layout = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL;
			m_pParent = nullptr;
		}
		VkAttachmentReference GetRef()const;
		uint32_t GetId()const;
		AttachmentHandle& Format(VkFormat _format);
		AttachmentHandle& LoadOp(VkAttachmentLoadOp _op, VkAttachmentLoadOp _stencil = VK_ATTACHMENT_LOAD_OP_DONT_CARE);
		AttachmentHandle& StoreOp(VkAttachmentStoreOp _op, VkAttachmentStoreOp _stencil = VK_ATTACHMENT_STORE_OP_DONT_CARE);
		AttachmentHandle& InitialLayout(VkImageLayout _layout);
		AttachmentHandle& FinalLayout(VkImageLayout _layout);
		AttachmentHandle& Samples(VkSampleCountFlagBits _samples);
	private:
		VkImageLayout m_layout;
		uint32_t m_sparseId;
		RenderPassCreateInfoBuilder* m_pParent;
	};
	class SubpassHandle
	{
	public:
		SubpassHandle(uint32_t idx, RenderPassCreateInfoBuilder* _pParent)
		{
			m_sparseId = idx;
			m_pParent = _pParent;
		}
		SubpassHandle()
		{
			m_sparseId = UINT32_MAX;
			m_pParent = nullptr;
		}
		uint32_t GetRef()const;
		uint32_t GetId()const;

		SubpassHandle& InputAttachments(AttachmentHandle* _pRefs, uint32_t _count);
		SubpassHandle& ColorAttachments(AttachmentHandle* _pRefs, uint32_t _count,
			AttachmentHandle* _pResolveRefs = nullptr);
		SubpassHandle& PreserveAttachments(AttachmentHandle* _pRefs, uint32_t _count);
		SubpassHandle& DepthAttachment(AttachmentHandle _ref);
	private:
		uint32_t m_sparseId;
		RenderPassCreateInfoBuilder* m_pParent;
	};

class RenderPassCreateInfoBuilder
{
public:
	friend class AttachmentHandle;
	friend class SubpassHandle;
	RenderPassCreateInfoBuilder();
	~RenderPassCreateInfoBuilder();
	AttachmentHandle AddColorAttachment();
	SubpassHandle AddSubpass();
	VkRenderPassCreateInfo Build();

private:
	VkAttachmentDescription* GetAttachmentDescription(AttachmentHandle _handle);
	uint32_t GetAttachmentIdx(AttachmentHandle _handle)const;
	SubpassDescriptionBuilder* GetSubpassDescription(SubpassHandle _handle);
	uint32_t GetSubpassIdx(SubpassHandle _handle)const;
	Lib::Container::SparseVector<VkAttachmentDescription> m_attachmentDescriptions;
	Lib::Container::SparseVector<SubpassDescriptionBuilder> m_subpassBuilders;
	Lib::Container::Vector<VkSubpassDependency> m_subpassDependencies;
	Lib::Container::Vector<VkSubpassDescription> m_subpasses;
};
}
#include "VulkanWrapper/RenderPassCreateInfo.inl"