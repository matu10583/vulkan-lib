#pragma once
#include <functional>

namespace Lib{
namespace Container{
	template <typename Derived>
	class FilterDispatchable;

	template<typename Enumerable>
	class BasicEnumerator
		:public FilterDispatchable<BasicEnumerator<Enumerable>>
	{
	public:
		using value_type = typename Enumerable::value_type;
		using iterator = typename Enumerable::iterator;
		BasicEnumerator(
			Enumerable* _enumerable
		)
			:m_pEnumerable(_enumerable)
			, m_counter(0)
			, m_current(_enumerable->Begin())
			, m_first(true)
		{}
		bool MoveNext() {
			if (!m_first) {
				++m_current;
				++m_counter;
			}
			m_first = false;
			if (m_current == m_pEnumerable->End()) return false;
			return true;
		}
		void Reset() {
			m_current = m_pEnumerable->Begin();
			m_counter = 0;
		}
		value_type& Current() {
			return *m_current;
		}
		int32_t CurrentIndex() {
			return m_counter;
		}

	private:
		bool m_first;
		int32_t m_counter;
		iterator m_current;
		Enumerable* m_pEnumerable;
	};

	template<typename T>
	class RangeEnumerator
		:public FilterDispatchable<RangeEnumerator<T>>
	{
	public:
		using value_type = T;
		using iterator = T*;
		RangeEnumerator(
			T* _pBegin,
			uint32_t _count
		)
			:m_counter(0)
			, m_current(_pBegin)
			, m_first(true)
			,m_pBegin(_pBegin)
			,m_pEnd(_pBegin+_count)
		{}
		bool MoveNext() {
			if (!m_first) {
				++m_current;
				++m_counter;
			}
			m_first = false;
			if (m_current == m_pEnd) return false;
			return true;
		}
		void Reset() {
			m_current = m_pBegin;
			m_counter = 0;
		}
		value_type& Current() {
			return *m_current;
		}
		int32_t CurrentIndex() {
			return m_counter;
		}

	private:
		bool m_first;
		int32_t m_counter;
		iterator m_current;
		iterator const m_pBegin;
		iterator const m_pEnd;
	};
	template<typename T>
	RangeEnumerator<T> MakeRange(T* _pBegin, uint32_t _count) {
		return RangeEnumerator<T>(_pBegin, _count);
	}



	template<typename Enumerator, typename TSelector, int ArgCount>
	class SelectEnumerator;

	template<typename Enumerator,typename TSelector>
	class SelectEnumerator<Enumerator, TSelector, 1>
		:public FilterDispatchable<SelectEnumerator<Enumerator, TSelector, 1>>
	{
	public:
		static TSelector get_selector();
		static typename Enumerator::value_type get_value();
		using value_type = decltype(get_selector()(get_value()));
		SelectEnumerator(
			Enumerator _enum,
			TSelector _selector
		)
			:m_enumerator(_enum)
			, m_selector(_selector){}

		value_type Current() {
			return m_selector(m_enumerator.Current());
		}



		bool MoveNext() {
			return m_enumerator.MoveNext();
		}
		void Reset() {
			m_enumerator.Reset();
		}
		int32_t CurrentIndex() {
			return m_enumerator.CurrentIndex();
		}


	private:
		Enumerator m_enumerator;
		TSelector m_selector;
	};

	template<typename Enumerator, typename TSelector>
	class SelectEnumerator<Enumerator, TSelector, 2>
		:public FilterDispatchable<SelectEnumerator<Enumerator, TSelector, 2>>
	{
	public:
		static TSelector get_selector();
		static typename Enumerator::value_type get_value();
		using value_type = decltype(get_selector()(get_value(), 0));
		SelectEnumerator(
			Enumerator _enum,
			TSelector _selector
		)
			:m_enumerator(_enum)
			, m_selector(_selector) {}

		value_type Current() {
			return m_selector(m_enumerator.Current(), m_enumerator.CurrentIndex());
		}



		bool MoveNext() {
			return m_enumerator.MoveNext();
		}
		void Reset() {
			m_enumerator.Reset();
		}
		int32_t CurrentIndex() {
			return m_enumerator.CurrentIndex();
		}


	private:
		Enumerator m_enumerator;
		TSelector m_selector;
	};

}
}
#include "Lib/Container/Generator.inl"