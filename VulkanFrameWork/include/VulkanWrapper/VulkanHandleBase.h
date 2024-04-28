#pragma once
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
	//�n���h�����b�p�[�����̂܂܃n���h���Ƃ��Ĉ��������̂Ōp����ł̓����o�͎����Ă͂����Ȃ�
	template<typename T>
class VulkanHandleBase
{
public:
	VulkanHandleBase()
		:m_vkHandle(VK_NULL_HANDLE)
	{}
	virtual ~VulkanHandleBase(){}
	operator T ()const {
		return m_vkHandle;
	}
	T GetVulkanHandle()const {
		return m_vkHandle;
	}
	T* VulkanHandleData() {
		return &m_vkHandle;
	}

protected:
	T m_vkHandle;
};
}

