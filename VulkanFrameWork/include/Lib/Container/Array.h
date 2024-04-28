#pragma once
#include <cstdint>
#include <utility>
#include <stdexcept>
namespace Lib{
namespace Container{
    template<typename T, size_t Size>
class Array
{
public:
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
        Array(){}
        ~Array(){}
		Array(T const& fill);
        reference operator[](size_type idx);
        const_reference operator[](size_type idx)const;
		size_type Length()const;
		const_pointer Data()const;
private:
    T m_array[Size];
};

template<typename T, std::size_t Size>
Array<T, Size>::Array(T const& fill) {
	for (uint32_t i = 0; i < Size; i++) {
		m_array[i] = fill;
	}
}


template<typename T, std::size_t Size>
inline typename Array<T, Size>::reference
Array<T, Size>::operator[](size_type idx)
{
	if (Length() <= idx) {
		throw std::out_of_range("index error");
	}
	return m_array[idx];
}
template<typename T, std::size_t Size>
inline typename Array<T, Size>::const_reference
Array<T, Size>::operator[](size_type idx) const
{
	if (Length() <= idx) {
		throw std::out_of_range("index error");
	}
	return m_array[idx];
}

template<typename T, std::size_t Size>
inline typename Array<T, Size>::size_type
Array<T, Size>::Length() const
{
	return Size;
}
template<typename T, size_t Size>
inline typename Array<T, Size>::const_pointer Array<T, Size>::Data() const
{
	return &m_array[0];
}
}

}
