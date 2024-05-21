#pragma once
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
	//ハンドルラッパーをそのままハンドルとして扱いたいので継承先ではメンバは持ってはいけない.destructorはvirtual出ないことに注意
	template<typename T>
class VulkanHandleBase
{
public:
	VulkanHandleBase()
		:m_vkHandle(VK_NULL_HANDLE)
	{}
	~VulkanHandleBase(){}
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

