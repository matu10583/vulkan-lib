#include "UnqPtr.h"
#pragma once
namespace Lib{
namespace Container{
	template<typename T, typename ...Args>
	inline UnqPtr<T> MakeUnique(Args && ...args)
	{
		return UnqPtr<T>(new T(args...));
	}

}
}
