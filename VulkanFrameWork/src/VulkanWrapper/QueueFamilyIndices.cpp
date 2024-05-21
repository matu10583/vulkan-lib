#include "VulkanWrapper/QueueFamilyIndices.h"
#include "VulkanWrapper/Surface.h"

namespace VulkanWrapper{
	QueueFamilyIndices::QueueFamilyIndices(PhysicalDeviceHandle _handle, SurfaceHandle _surface)
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
			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(_handle.GetVulkanHandle(), i, _surface.GetVulkanHandle(), &presentSupport);
			if (!HasQueue(QueueFamilyType::PRESENT) &&
				presentSupport) {
				m_availableFlag |= QueueFamilyTypeBit::PRESENT_BIT;
				m_indices[QueueFamilyType::PRESENT] = i;
			}

			if (IsComplete()) break;
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
	bool QueueFamilyIndices::IsComplete() const
	{
		return  (m_availableFlag & QueueFamilyTypeBit::ALL) == QueueFamilyTypeBit::ALL;
	}
	void QueueFamilyIndices::CreateIndexSet(Lib::Container::Set<uint32_t>* out, uint32_t queue_bit)
	{
		out->Clear();
		for (uint32_t i = 0; i < QueueFamilyType::COUNT; i++)
		{
			if ((queue_bit & (1 << i)) != (1<<i)) continue;
			out->Insert(m_indices[i]);
		}
	}
}

