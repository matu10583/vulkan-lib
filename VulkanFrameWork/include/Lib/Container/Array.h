#pragma once
#include <cstddef>
#include <iterator>
#include <initializer_list>

namespace Lib {
	namespace Container {
		template<typename Enumerable>
		class BasicEnumerator;

		template<typename T, std::size_t Size>
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

			Array();
			~Array();
			Array(T&& _fill);
			Array(std::initializer_list<T>);
			T& operator[](std::size_t _idx);
			T const& operator[](std::size_t _idx)const ;

			iterator Begin();
			iterator End();
			const_iterator CBegin();
			const_iterator CEnd();

			BasicEnumerator<Array<T, Size>>
				GetFilter();

		private:
			T m_array[Size];
		};
	}
}

#include "Lib/Container/Array.inl"