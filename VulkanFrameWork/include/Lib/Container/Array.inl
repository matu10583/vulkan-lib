#pragma once
#include "Lib/Utility/Macro.h"
#include "Lib/Container/Generator.h"
#include "Array.h"

namespace Lib{
namespace Container{
	template<typename T, std::size_t Size>
	inline Array<T, Size>::Array()
	{
	}

	template<typename T, std::size_t Size>
	inline Array<T, Size>::~Array()
	{
	}

	template<typename T, std::size_t Size>
	inline Array<T, Size>::Array(T&& _fill)
	{
		foreach(itr, (*this)) {
			*itr = _fill;
		}
	}

	template<typename T, std::size_t Size>
	inline Array<T, Size>::Array(std::initializer_list<T> _init)
	{
		auto itr = _init.begin();
		for (int32_t i = 0; i < Size && itr != _init.end(); i++, itr++) {
			m_array[i] = *itr;
		}
	}

	template<typename T, std::size_t Size>
	inline T& Array<T, Size>::operator[](std::size_t _idx)
	{
		return m_array[_idx];
		// TODO: return ステートメントをここに挿入します
	}

	template<typename T, std::size_t Size>
	inline T const& Array<T, Size>::operator[](std::size_t _idx) const
	{
		return m_array[_idx];
		// TODO: return ステートメントをここに挿入します
	}

	template<typename T, std::size_t Size>
	inline typename Array<T, Size>::iterator Array<T, Size>::Begin()
	{
		return &m_array[0];
	}

	template<typename T, std::size_t Size>
	inline typename Array<T, Size>::iterator Array<T, Size>::End()
	{
		return &m_array[Size - 1]+1;
	}

	template<typename T, std::size_t Size>
	inline typename Array<T, Size>::const_iterator Array<T, Size>::CBegin()
	{
		return &m_array[0];
	}

	template<typename T, std::size_t Size>
	inline typename Array<T, Size>::const_iterator Array<T, Size>::CEnd()
	{
		return &m_array[Size - 1]+1;
	}

	template<typename T, std::size_t Size>
	inline BasicEnumerator<Array<T, Size>> Array<T, Size>::GetFilter()
	{
		return BasicEnumerator<Array<T, Size>>(this);
	}

}
}
