#pragma once
#include "Lib/Container/Generator.h"
#include <functional>

namespace Lib{
namespace Container{

	template<typename Derived>
	class FilterDispatchable {
	public:
		template<typename TSelector>
		decltype(auto) Select(
			TSelector _selector);

		decltype(auto) ToVector();
	};

}
}
#include "Lib/Container/FilterDispatchable.inl"