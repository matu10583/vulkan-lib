#pragma once
#include "Lib/Container/IVector.h"
#include <memory>

namespace Lib{
namespace Container{
	template<typename T, typename Allocator = std::allocator<T>>
class Vector
: public Lib::Container::IVector<T, std::size_t>
{
public:
	using allocator_type = Allocator;
	using alloc_traits = std::allocator_traits<Allocator>;

	using typename IVector<T, std::size_t>::size_type;
	using typename IVector<T, size_type>::value_type;
	using typename IVector<T, size_type>::pointer;
	using typename IVector<T, size_type>::const_pointer;
	using typename IVector<T, size_type>::reference;
	using typename IVector<T, size_type>::const_reference;
	using typename IVector<T, size_type>::iterator;
	using typename IVector<T, size_type>::const_iterator;
	using typename IVector<T, size_type>::reverse_iterator;
	using typename IVector<T, size_type>::const_reverse_iterator;
	using typename IVector<T, size_type>::difference_type;

	Vector(size_type reserve = 0, allocator_type a = allocator_type());
	~Vector();
	virtual void EmplaceBack(T&& elem) override;
	virtual reference operator[](size_type idx) override;
	virtual const_reference operator[](size_type idx)const override;
	virtual void Clear() override;
	virtual size_type Length()const override;
	virtual size_type Capacity()const override;
	virtual iterator Begin() override;
	virtual iterator End() override;
	virtual const_iterator CBegin()const override;
	virtual const_iterator CEnd()const override;
	void Reserve(size_type reserve);
	void Resize(size_type size);

	std::string printDebug() {

	}
private:
	T* m_pFirst;
	T* m_pEnd;
	T* m_pReservedEnd;
	allocator_type m_allocator;

};
template<typename T, typename Allocator>
inline Vector<T, Allocator>::Vector(Vector<T,Allocator>::size_type reserve,
	allocator_type a)
	:m_allocator(a)
	,m_pFirst(nullptr)
	,m_pEnd(nullptr)
	,m_pReservedEnd(nullptr)
{
	Reserve(reserve);
	m_pEnd = m_pFirst;
}

template<typename T, typename Allocator>
inline Vector<T, Allocator>::~Vector()
{
	Clear();
	alloc_traits::deallocate(m_allocator, m_pFirst, Length());
	m_pFirst = m_pReservedEnd = m_pEnd = nullptr;
}

template<typename T, typename Allocator>
inline void Vector<T, Allocator>::EmplaceBack(T&& elem) {
	if (Capacity() == 0) {
		m_pFirst = alloc_traits::allocate(m_allocator, 1);
		m_pReservedEnd = m_pFirst + 1;
		m_pEnd = m_pFirst;

	}
	else if (Length() >= Capacity()) {
		iterator tmp_begin = m_pFirst;
		iterator tmp_end = m_pEnd;
		size_type tmp_size = Length();
		size_type reserve = tmp_size * 2;
		m_pFirst = alloc_traits::allocate(m_allocator, reserve);
		m_pReservedEnd = m_pFirst + reserve;
		m_pEnd = std::move(tmp_begin, tmp_end, m_pFirst);
	}

	*m_pEnd = std::move(elem);
	m_pEnd++;
}
template<typename T, typename Allocator>
inline typename Vector<T, Allocator>::reference
Vector<T, Allocator>::operator[](size_type idx) {
	if (Length() <= idx) {
		throw std::out_of_range("idx error");
	}
	return m_pFirst[idx];
}
template<typename T, typename Allocator>
inline typename Vector<T, Allocator>::const_reference
Vector<T, Allocator>::operator[](size_type idx)const {
	if (Length() <= idx) {
		throw std::out_of_range("idx error");
	}
	return m_pFirst[idx];
}
template<typename T, typename Allocator>
inline void  Vector<T, Allocator>::Clear() {
	for (iterator elem = Begin(); elem < End(); elem++) {
		alloc_traits::destroy(m_allocator, elem);
	}
	m_pEnd = m_pFirst;
}

template<typename T, typename Allocator>
inline typename Vector<T, Allocator>::size_type
Vector<T, Allocator>::Capacity()const {
	return m_pReservedEnd - m_pFirst;
}

template<typename T, typename Allocator>
inline typename Vector<T, Allocator>::size_type
Vector<T, Allocator>::Length()const {
	return m_pEnd - m_pFirst;
}

template<typename T, typename Allocator>
inline typename Vector<T, Allocator>::iterator
Vector<T, Allocator>::Begin() {
	return m_pFirst;
}
template<typename T, typename Allocator>
inline typename Vector<T, Allocator>::iterator
Vector<T, Allocator>::End() {
	return m_pEnd;
}
template<typename T, typename Allocator>
inline typename Vector<T, Allocator>::const_iterator
Vector<T, Allocator>::CBegin()const {
	return m_pFirst;
}
template<typename T, typename Allocator>
inline typename Vector<T, Allocator>::const_iterator
Vector<T, Allocator>::CEnd()const {
	return m_pEnd;
}
template<typename T, typename Allocator>
inline void Vector<T, Allocator>::Reserve(size_type reserve)
{
	if (Capacity() >= reserve) return;
	m_pFirst = alloc_traits::allocate(m_allocator, reserve);
	if (m_pEnd == nullptr) m_pEnd = m_pFirst;
	m_pReservedEnd = m_pFirst + reserve;

}

template<typename T, typename Allocator>
inline void Vector<T, Allocator>::Resize(size_type size)
{
	if (Length() == size) return;
	if (Length() > size) {
		for (uint32_t i = size - 1; i < Length(); i++) {
			alloc_traits::destroy(m_allocator, m_pFirst + i);
		}
		m_pEnd = m_pFirst + size;
		return;
	}
	Reserve(size);
	for (uint32_t i = Length(); i < size; i++) {
		alloc_traits::construct(m_allocator, m_pFirst + i);
	}
	m_pEnd = m_pFirst + size;

}

}
}

