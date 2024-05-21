#pragma once
#include <vulkan/vulkan.h>
namespace VulkanWrapper{
	struct ImageInfo2D
	{
		VkFormat Format;
		VkExtent2D Extent;
		VkImageUsageFlagBits Usage;
	};
	struct SurfaceInfo2D
	{
		ImageInfo2D Image;
		VkColorSpaceKHR ColorSpace;
	};

}
