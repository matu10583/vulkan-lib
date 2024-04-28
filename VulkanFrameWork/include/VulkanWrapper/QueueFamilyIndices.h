#pragma once
#include "VulkanWrapper/Instance.h"
#include "Lib/Container/Array.h"
namespace VulkanWrapper{
	enum QueueFamilyType
	{
		GRAPHICS=0,
		PRESENT=1,
		COUNT = 2
	};
	enum QueueFamilyTypeBit
	{
		NONE = 0,
		GRAPHICS_BIT = 1<<QueueFamilyType::GRAPHICS,
		PRESENT_BIT = 1<<QueueFamilyType::PRESENT,
	};
class QueueFamilyIndices
{
public:
	QueueFamilyIndices(
		PhysicalDeviceHandle _handle
	);
	bool HasQueue(QueueFamilyType t)const;
	uint32_t GetIndex(QueueFamilyType t)const;
private:
	uint64_t m_availableFlag;
	Lib::Container::Array<uint32_t, QueueFamilyType::COUNT> m_indices;
};
}

