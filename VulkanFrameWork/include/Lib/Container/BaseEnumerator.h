#pragma once
#include "Lib/Container/IEnumerator.h"
#include <functional>

namespace Lib{
namespace Container{

	template<typename Iterator>
	class BasicEnumerator
		:public IEnumerator<Iterator>
	{
	public:

		BasicEnumerator(
			Iterator _begin,
			Iterator _end
		)
			:m_begin(_begin)
			,m_end(_end)
			,m_current(_begin)
		{}

		bool MoveNext()override {
			++m_current;
			if (m_current == m_end) {
				return false;
			}
			return true;
		}
		Iterator Current()override {
			return m_current;
		}
		void Reset()override {
			m_current = m_begin;
		}
	private:
		Iterator m_current;
		Iterator const m_begin;
		Iterator const m_end;
	};

	template<typename Enumerator, typename Tsource, typename TResult>
	class SelectEnumerator
		:public IEnumerator<TResult>
	{
	public:
		SelectEnumerator(
			Enumerator _enum,
			std::function<TResult(TSource const&, int32_t)> _selector
		)
			:m_enumerator(_enum)
			,m_selector(_selector)
		{

		}

		bool MoveNext()override {
			return m_enumerator.MoveNext();
		}
		TResult Current()override {
			return m_selector(m_enumerator.Current());
		}
		void Reset()override {
			m_enumerator.Reset();
		}
	private:
		std::function<TResult(TSource const&, int32_t)> m_selector;
		Enumerator m_enumerator;
	};

}
}
#include "Lib/Container/BaseEnumerator.inl"