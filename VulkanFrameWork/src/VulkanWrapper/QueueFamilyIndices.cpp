#include "VulkanWrapper/QueueFamilyIndices.h"
namespace VulkanWrapper{
	QueueFamilyIndices::QueueFamilyIndices(PhysicalDeviceHandle _handle)
		:m_availableFlag(0)
		,m_indices(UINT32_MAX)
	{
		Lib::Container::Vector<VkQueueFamilyProperties> queueProps{};
		queueProps.Resize(_handle.GetQueueFamilyCount());
		_handle.GetQueueFamilyProperties(
			queueProps.Data(), queueProps.Length()
		);
		uint32_t i = 0;
		for (auto itr = queueProps.Begin(); itr < queueProps.End(); itr++) {
			if (!HasQueue(QueueFamilyType::GRAPHICS) &&
				itr->queueFlags &
				(VK_QUEUE_GRAPHICS_BIT)) {
				m_availableFlag |= QueueFamilyTypeBit::GRAPHICS_BIT;
				m_indices[QueueFamilyType::GRAPHICS] = i;
			}
		}
	}
	bool QueueFamilyIndices::HasQueue(QueueFamilyType t) const
	{
		QueueFamilyTypeBit bit = 
			static_cast<QueueFamilyTypeBit>(1 << t);
		return m_availableFlag & bit;
	}
	uint32_t QueueFamilyIndices::GetIndex(QueueFamilyType t) const
	{
		if (!HasQueue(t)) {
			return UINT32_MAX;
		}
		return m_indices[t];
	}
}

