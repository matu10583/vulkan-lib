#pragma once
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
    //派生先のサイズを変えたくないのでCRTPを使ってみる。変に複雑な解法だったらごめん。
    template<typename Derived>
    class IVertexData {

    public:
        //pOutBindsがnullptrの場合、属性の数を返す
        static constexpr uint32_t GetBindingDescriptions(VkVertexInputBindingDescription* pOutBinds) {
            return Derived::GetBindingDescriptions_Impl(pOutBinds);
        }
        //pOutAttrsがnullptrの場合、属性の数を返す
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
