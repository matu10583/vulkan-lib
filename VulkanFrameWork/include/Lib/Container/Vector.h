#pragma once
#include <memory>
#include <stdexcept>

namespace Lib {
	namespace Container {
		template<typename Enumerable>
		class BasicEnumerator;

		template<typename T, typename Allocator = std::allocator<T>>
		class Vector
		{
		public:
			using allocator_type = Allocator;
			using alloc_traits = std::allocator_traits<Allocator>;

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

			Vector(size_type reserve = 0, allocator_type a = allocator_type());
			Vector(Vector&& _v);
			Vector<T, Allocator>& operator=(Vector&& v);
			~Vector();
			void EmplaceBack(T&& elem) ;
			reference operator[](size_type idx) ;
			const_reference operator[](size_type idx)const ;
			void Clear() ;
			size_type Length()const ;
			size_type Capacity()const ;
			iterator Begin();
			iterator End();
			const_iterator CBegin()const;
			const_iterator CEnd()const;
			void Reserve(size_type reserve);
			void Resize(size_type size);
			pointer Data();
			const_pointer Data()const;
			bool Empty()const;
			T const& CBack()const;
			T& Back();
			BasicEnumerator<Vector<T, Allocator>> GetEnumerator();
		private:
			T* m_pFirst;
			T* m_pEnd;
			T* m_pReservedEnd;
			allocator_type m_allocator;

		};


	}
}

#include "Lib/Container/Vector.inl"