#pragma once
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
    //�h����̃T�C�Y��ς������Ȃ��̂�CRTP���g���Ă݂�B�ςɕ��G�ȉ�@�������炲�߂�B
    template<typename Derived>
    class IVertexData {

    public:
        //pOutBinds��nullptr�̏ꍇ�A�����̐���Ԃ�
        static constexpr uint32_t GetBindingDescriptions(VkVertexInputBindingDescription* pOutBinds) {
            return Derived::GetBindingDescriptions_Impl(pOutBinds);
        }
        //pOutAttrs��nullptr�̏ꍇ�A�����̐���Ԃ�
        static constexpr uint32_t GetAttributeDescriptions(VkVertexInputAttributeDescription* pOutAttrs) {
            return Derived::GetAttributeDescriptions_Impl(pOutAttrs);
        }
    };
    class TestVertex
        :public IVertexData<TestVertex> {
    public:
        static constexpr uint32_t GetBindingDescriptions_Impl(VkVertexInputBindingDescription* pOutBinds) {
            if (pOutBinds == nullptr) {
                return 0;
            }
            return 0;
        }
        static constexpr uint32_t GetAttributeDescriptions_Impl(VkVertexInputAttributeDescription* pOutAttrs) {
            if (pOutAttrs == nullptr) {
                return 0;
            }
            return 0;
        }
    };
}
