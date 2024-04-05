#pragma onc

namespace VulkanWrapper {
	template<typename Handle>
	class IHandleWrapper
	{
	public:
		virtual Handle GetHandle()const = 0;
	};

}

