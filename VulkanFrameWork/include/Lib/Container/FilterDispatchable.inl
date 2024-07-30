#pragma once
#include "Lib/Container/Generator.h"
#include "Lib/Container/Vector.h"
#include "Lib/Utility/TypeTraits.h"

namespace Lib{
namespace Container{


	template<typename Derived>
	template<typename TSelector>
	inline decltype(auto) FilterDispatchable<Derived>::Select(TSelector _selector)
	{
		return SelectEnumerator<Derived, TSelector, 
		Lib::Utility::ArgCounter<decltype(&TSelector::operator())>::value>(
			*reinterpret_cast<Derived*>(this), _selector);
	}



	template<typename Derived>
	inline decltype(auto) FilterDispatchable<Derived>::ToVector()
	{
		Vector<Derived::value_type> ret{};
		Derived& enm = *reinterpret_cast<Derived*>(this);
		while(enm.MoveNext()) {
			ret.EmplaceBack(std::move(enm.Current()));
		}
		return ret;
	}
}
}
