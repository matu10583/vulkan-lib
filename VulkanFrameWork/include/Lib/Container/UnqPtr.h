#pragma once
#include "Lib/Utility/Macro.h"
namespace Lib{
namespace Container{


	template<typename T, typename D = _DefaultDeleter<T>>
class UnqPtr
{
public:
	UnqPtr(){}
	explicit UnqPtr(T* _ptr)
		:m_ptr(_ptr){}
	~UnqPtr() {
		if (m_ptr) D(m_ptr);
		m_ptr = nullptr;
	}
	UnqPtr(UnqPtr const&) = delete;
	UnqPtr& operator=(UnqPtr const&) = delete;
	UnqPtr(UnqPtr&& o)
		:m_ptr(o.m_ptr) {
		o.m_ptr = nullptr;
	}
	UnqPtr& operator=(UnqPtr&& o) {
		if (m_ptr) D(m_ptr);
		m_ptr = o.m_ptr;
		o.m_ptr = nullptr;
		return *this;
	}
	T& operator*()noexcept { return *m_ptr; }
	T* operator ->()noexcept { return m_ptr; }
	T* get()noexcept { return m_ptr; }
private:
	T* m_ptr = nullptr;
};
template <typename T,typename... Args>
UnqPtr<T> MakeUnique(Args&&... args);




}
}
#include "Lib/Container/UnqPtr.inl"