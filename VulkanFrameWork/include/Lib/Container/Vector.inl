#pragma once
#include "Lib/Container/Generator.h"
#include "Vector.h"
namespace Lib{
	namespace Container {
		template<typename T, typename Allocator>
		inline Vector<T, Allocator>::Vector(Vector<T, Allocator>::size_type reserve,
			allocator_type a)
			:m_allocator(a)
			, m_pFirst(nullptr)
			, m_pEnd(nullptr)
			, m_pReservedEnd(nullptr)
		{
			Reserve(reserve);
			m_pEnd = m_pFirst;
		}

		template<typename T, typename Allocator>
		inline Vector<T, Allocator>::Vector(Vector&& _v)
			:m_allocator(std::move(_v.m_allocator))
			,m_pFirst(std::move(_v.m_pFirst))
			,m_pEnd(std::move(_v.m_pEnd))
			,m_pReservedEnd(std::move(_v.m_pReservedEnd))
		{
			_v.m_pFirst = nullptr;
			_v.m_pEnd = nullptr;
			_v.m_pReservedEnd = nullptr;
		}

		template<typename T, typename Allocator>
		inline Vector<T, Allocator>& Vector<T, Allocator>::operator=(Vector&& _v)
		{
			m_allocator = std::move(_v.m_allocator);
			m_pFirst = std::move(_v.m_pFirst);
			_v.m_pFirst = nullptr;
			m_pEnd = std::move(_v.m_pEnd);
			_v.m_pEnd = nullptr;
			m_pReservedEnd = std::move(_v.m_pReservedEnd);
			_v.m_pReservedEnd = nullptr;
			return *this;
		}

		template<typename T, typename Allocator>
		inline Vector<T, Allocator>::~Vector()
		{
			Clear();
			alloc_traits::deallocate(m_allocator, m_pFirst, Capacity());
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
				for (size_type i = size - 1; i < Length(); i++) {
					alloc_traits::destroy(m_allocator, m_pFirst + i);
				}
				m_pEnd = m_pFirst + size;
				return;
			}
			Reserve(size);
			for (size_type i = Length(); i < size; i++) {
				alloc_traits::construct(m_allocator, m_pFirst + i);
			}
			m_pEnd = m_pFirst + size;

		}

		template<typename T, typename Allocator>
		inline typename Vector<T, Allocator>::pointer
			Vector<T, Allocator>::Data()
		{
			return m_pFirst;
		}

		template<typename T, typename Allocator>
		inline typename Vector<T, Allocator>::const_pointer Vector<T, Allocator>::Data() const
		{
			return m_pFirst;
		}

		template<typename T, typename Allocator>
		inline bool Lib::Container::Vector<T, Allocator>::Empty()const
		{
			return Length() == 0;
		}
		template<typename T, typename Allocator>
		inline T const& Vector<T, Allocator>::CBack() const
		{
			return this[Length() - 1];
			// TODO: return ステートメントをここに挿入します
		}

		template<typename T, typename Allocator>
		inline T& Vector<T, Allocator>::Back()
		{
			return *(m_pEnd - 1);
			// TODO: return ステートメントをここに挿入します
		}


		template<typename T, typename Allocator>
		inline BasicEnumerator<
			Vector<T, Allocator>> 
			Vector<T, Allocator>::GetEnumerator()
		{
			return BasicEnumerator<
			Vector<T, Allocator>>(this);
		}
}
}
