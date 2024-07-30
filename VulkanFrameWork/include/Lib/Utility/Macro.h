#pragma once
#define foreach(i, c) for(auto i = c.Begin(); i!=c.End();++i)
#define const_foreach(i, c) for(auto i = c.CBegin(); i!=c.CEnd();++i)


template<typename T>
class _DefaultDeleter {
	void operator()(T* _ptr)const {
		delete _ptr;
	}
};
template<typename T>
class _DefaultDeleter<T[]> {
	void operator()(T* _ptr)const {
		delete[] _ptr;
	}
};

template<typename T>
inline void SAFE_DELETE(T * &p) {
	typedef char type_must_be_complete[sizeof(T) ? 1 : -1];
	(void)sizeof(type_must_be_complete);
	delete p;
	p = nullptr;
}
template<typename T>
inline void SAFE_DELETE_ARR(T * &p) {
	typedef char type_must_be_complete[sizeof(T) ? 1 : -1];
	(void)sizeof(type_must_be_complete);
	delete[] p;
	p = nullptr;
}

namespace Lib{
namespace Utility{

}
}
#include "Lib/Utility/Macro.inl"