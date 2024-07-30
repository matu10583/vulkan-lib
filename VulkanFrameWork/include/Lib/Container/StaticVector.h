#pragma once
#include <cstdint>
#include <utility>
#include <stdexcept>
namespace Lib{
namespace Container{
	template<typename Enumerable>
	class BasicEnumerator;

	template<typename T, std::size_t Size>
class StaticVector
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
	BasicEnumerator<StaticVector<T, Size>> GetEnumerator();
private:
	value_type m_array[Size];
	pointer m_pEnd;
	pointer const m_pReservedEnd;
};

}
}

#include "Lib/Container/StaticVector.inl"