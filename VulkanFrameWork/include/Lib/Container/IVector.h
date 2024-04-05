#pragma once
#include <cstdint>
#include <cstddef>
#include <iterator>
#include <iostream>
namespace Lib{
namespace Container{
	template<typename T, typename size_t = std::size_t>
class IVector
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

	virtual ~IVector(){}
	virtual void EmplaceBack(T&& elem) = 0;
	virtual reference operator[](size_type idx) = 0;
	virtual const_reference operator[](size_type idx)const = 0;
	virtual void Clear() = 0;
	virtual size_type Capacity()const = 0;
	virtual iterator Begin() = 0;
	virtual iterator End() = 0;
	virtual const_iterator CBegin()const = 0;
	virtual const_iterator CEnd()const = 0;

	virtual size_type Length()const = 0;

};
}
}

