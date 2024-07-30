#pragma once
#include "Lib/Container/Generator.h"
namespace Lib{
namespace Container{
	template<typename T, std::size_t Size>
	inline StaticVector<T, Size>::StaticVector()
		:m_pReservedEnd(&(m_array[Size - 1]))
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
		return CEnd() - CBegin();
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
			if (*itr == e) {
				return i;
			}
			i++;
		}
		return UINT32_MAX;
	}

	template<typename T, std::size_t Size>
	inline BasicEnumerator<StaticVector<T, Size>> StaticVector<T, Size>::GetEnumerator()
	{
		return BasicEnumerator<
			StaticVector<T, Size>>(this);
	}

	template<typename T, std::size_t Size>
	inline typename StaticVector<T, Size>::pointer
		StaticVector<T, Size>::Data()
	{
		return static_cast<T*>(m_array);
	}
}
}
