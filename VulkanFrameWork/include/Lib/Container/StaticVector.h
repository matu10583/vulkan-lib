#pragma once
#include <cstdint>
#include <utility>
#include <stdexcept>
#include "Lib/Container/IVector.h"
namespace Lib{
namespace Container{
	template<typename T, std::size_t Size>
class StaticVector
	:public IVector<T, decltype(Size)>
{
	using typename  IVector<T, decltype(Size)>::size_type;
	using typename  IVector<T, size_type>::value_type;
	using typename  IVector<T, size_type>::pointer;
	using typename  IVector<T, size_type>::const_pointer;
	using typename  IVector<T, size_type>::reference;
	using typename  IVector<T, size_type>::const_reference;
	using typename  IVector<T, size_type>::iterator;
	using typename  IVector<T, size_type>::const_iterator;
	using typename  IVector<T, size_type>::reverse_iterator;
	using typename  IVector<T, size_type>::const_reverse_iterator;
public:
	StaticVector();
	~StaticVector();
	void EmplaceBack(T&& elem)override;
	reference operator[](size_type idx)override;
	const_reference operator[](size_type idx)const override;
	void Clear()override;
	size_type Capacity()const override;
	size_type Length()const override;
	iterator Begin() override;
	iterator End() override;
	const_iterator CBegin()const override;
	const_iterator CEnd()const override;
private:
	value_type m_array[Size];
	pointer m_pEnd;
	pointer const m_pReservedEnd;
};
template<typename T, std::size_t Size>
inline StaticVector<T, Size>::StaticVector()
	:m_pReservedEnd(&(m_array[Size-1]))
{
	m_pEnd = &(m_array[0]);
}
template<typename T, std::size_t Size>
inline StaticVector<T, Size>::~StaticVector()
{
}
template<typename T, std::size_t Size>
inline void StaticVector<T, Size>::EmplaceBack(T&& elem)
{
	if (Length() >= Capacity()) {
		throw std::out_of_range("index error");
	}
	*m_pEnd = std::move(elem);
	m_pEnd++;
}
template<typename T, std::size_t Size>
inline typename StaticVector<T, Size>::reference
StaticVector<T, Size>::operator[](size_type idx)
{
	if (Length() <= idx) {
		throw std::out_of_range("index error");
	}
	return m_array[idx];
}
template<typename T, std::size_t Size>
inline typename StaticVector<T, Size>::const_reference
StaticVector<T, Size>::operator[](size_type idx) const
{
	if (Length() <= idx) {
		throw std::out_of_range("index error");
	}
	return m_array[idx];
}
template<typename T, std::size_t Size>
inline void StaticVector<T, Size>::Clear()
{
	m_pEnd = &(m_array[0]);
}
template<typename T, std::size_t Size>
inline typename StaticVector<T, Size>::size_type StaticVector<T, Size>::Capacity() const
{
	return Size;
}
template<typename T, std::size_t Size>
inline typename StaticVector<T, Size>::size_type StaticVector<T, Size>::Length() const
{
	return CEnd()-CBegin();
}
template<typename T, std::size_t Size>
inline typename StaticVector<T, Size>::iterator StaticVector<T, Size>::Begin() 
{
	return static_cast<T*>(m_array);
}
template<typename T, std::size_t Size>
inline typename StaticVector<T, Size>::iterator StaticVector<T, Size>::End() 
{
	return m_pEnd;
}

template<typename T, std::size_t Size>
inline typename StaticVector<T, Size>::const_iterator
StaticVector<T, Size>::CBegin()const
{
	return static_cast<T const*>(m_array);
}
template<typename T, std::size_t Size>
inline typename StaticVector<T, Size>::const_iterator
StaticVector<T, Size>::CEnd()const
{
	return m_pEnd;
}
}
}

