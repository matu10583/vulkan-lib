#include "VulkanWrapper/InstanceExtensionSupport.h"
#include <set>
namespace VulkanWrapper{
        InstanceExtensionSupport::~InstanceExtensionSupport(){

        }
        bool InstanceExtensionSupport::AreSupported(char const** _pStrs, uint32_t _size) const
        {
            uint32_t count_found = 0;
            for (auto* itr = m_properties.CBegin(); itr != m_properties.CEnd(); itr++) {
                for (uint32_t i = 0u; i < _size; i++) {
                    if (strcmp(itr->extensionName, _pStrs[i]) == 0) {
                        count_found++;
                        break;
                    }
                }
            }
            return false;
        }
        InstanceExtensionSupport::InstanceExtensionSupport()
                {
            uint32_t extensionsCount;
            vkEnumerateInstanceExtensionProperties(
                nullptr, &extensionsCount, nullptr
            );
            m_properties.Resize(extensionsCount);
            vkEnumerateInstanceExtensionProperties(
                nullptr, &extensionsCount, m_properties.Data()
            );
        }
}
