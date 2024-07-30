#pragma once
#include "VulkanWrapper/Instance.h"
#include "Lib/Container/Array.h"
#include "Lib/Container/Set.h"
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
		ALL = (1<<QueueFamilyType::COUNT) - 1
	};
	class SurfaceHandle;
class QueueFamilyIndices
{
public:
	QueueFamilyIndices(
		
	);
	bool Init(
		PhysicalDeviceHandle _handle, SurfaceHandle _surface
	);
	bool HasQueue(QueueFamilyType t)const;
	uint32_t GetIndex(QueueFamilyType t)const;
	bool IsComplete()const;
	void CreateIndexSet(Lib::Container::Set<uint32_t>* out, uint32_t queue_bit = QueueFamilyTypeBit::ALL);
private:
	uint64_t m_availableFlag;
	Lib::Container::Array<uint32_t, QueueFamilyType::COUNT> m_indices;
};
}

