#pragma once
#include <cstdint>
#include <utility>
#include <stdexcept>
namespace Lib{
namespace Container{
	template<typename T, std::size_t Size>
class StaticVector
{
	using value_type = T;
	using pointer = T*;
	using const_pointer = T const*;
	using reference = value_type&;
	using const_reference = value_type const&;
	using size_type = size_t;
	using iterator = pointer;
	using const_iterator = const_pointer;
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;
	using difference_type = std::ptrdiff_t;
public:
	StaticVector();
	~StaticVector();
	void EmplaceBack(T&& elem);
	reference operator[](size_type idx);
	const_reference operator[](size_type idx)const ;
	void Clear();
	size_type Capacity()const ;
	size_type Length()const ;
	iterator Begin() ;
	iterator End() ;
	const_iterator CBegin()const ;
	const_iterator CEnd()const ;
	pointer Data();
	void Resize(uint32_t size);
	uint32_t Find(bool (*func)(T const&))const;
	uint32_t Find(T const&)const;
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

template<typename T, std::size_t Size>
inline void StaticVector<T, Size>::Resize(uint32_t size)
{
	if (size > Capacity()) {
		throw std::out_of_range("excess capacity");
	}
	m_pEnd = Data() + size;
}

template<typename T, std::size_t Size>
inline uint32_t StaticVector<T, Size>::Find(bool (*func)(T const&)) const
{
	uint32_t i = 0;
	for (auto* itr = Begin(); itr < End(); itr++) {
		if (func(*itr)) {
			return i;
		}
		i++;
	}
	return UINT32_MAX;
}

template<typename T, std::size_t Size>
inline uint32_t StaticVector<T, Size>::Find(T const& e) const
{
	uint32_t i = 0;
	for (auto* itr = Begin(); itr < End(); itr++) {
		if (*itr==e) {
			return i;
		}
		i++;
	}
	return UINT32_MAX;
}

template<typename T, std::size_t Size>
inline typename StaticVector<T, Size>::pointer
StaticVector<T, Size>::Data()
{
	return static_cast<T*>(m_array);
}
}
}

