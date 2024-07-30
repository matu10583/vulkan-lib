#include "SparseVector.h"
#include "Lib/Utility/Macro.h"
#include "Lib/Container/FilterDispatchable.h"
#pragma once
namespace Lib{
namespace Container{
	template<typename Object>
	inline typename SparseVector<Object>::SparseID
		SparseVector<Object>::Add(Object&& _obj)
	{
		m_elements.EmplaceBack(std::move(_obj));
		m_elemIndices.EmplaceBack(
			m_elements.Length() - 1
		);
		return m_elemIndices.Length() - 1;
	}

	template<typename Object>
	inline Object* Lib::Container::SparseVector<Object>::Get(SparseID _id)
	{
		ArrayIdx idx = GetIdx(_id);
		if (idx == GraveMark ||
			m_elements.Length()<=idx) {
			return nullptr;
		}
		return &m_elements[idx];
	}

	template<typename Object>
	inline typename SparseVector<Object>::ArrayIdx SparseVector<Object>::GetIdx(SparseID _id) const
	{
		if (_id >= m_elemIndices.Length()) return GraveMark;
		ArrayIdx idx = m_elemIndices[_id];
		return idx;
	}

	template<typename Object>
	inline typename SparseVector<Object>::SparseVectorEnumerator 
		SparseVector<Object>::GetEnumerator()
	{
		return SparseVectorEnumerator(this);
	}

	template<typename Object>
	inline uint32_t SparseVector<Object>::Length() const
	{
		uint32_t ret = 0;
		const_foreach(itr, m_elemIndices) {
			if (*itr == GraveMark) continue;
			ret++;
		}
		return ret;
	}

	template<typename Object>
	inline Object const* SparseVector<Object>::Data() const
	{
		return m_elements.Data();
	}

	template<typename Object>
	inline Object* SparseVector<Object>::Data()
	{
		return m_elements.Data();
	}



	template<typename Object>
	inline SparseVector<Object>::SparseVectorEnumerator::SparseVectorEnumerator(SparseVector<Object>* _pParent)
		:m_pParent(_pParent)
		,m_first(true)
	{
		Reset();
	}

	template<typename Object>
	inline bool SparseVector<Object>::SparseVectorEnumerator::MoveNext()
	{
		if (!m_first) {
			++m_current;
			++m_counter;
		}
		m_first = false;
		while(true) {
			if (m_current == m_pParent->m_elemIndices.End()) return false;
			if (*m_current != SparseVector<Object>::GraveMark) break;
			++m_current;
		}
		return true;
	}

	template<typename Object>
	inline void SparseVector<Object>::SparseVectorEnumerator::Reset()
	{
		m_counter = 0;
		m_current = m_pParent->m_elemIndices.Begin();
	}

	template<typename Object>
	inline typename SparseVector<Object>::SparseVectorEnumerator::value_type& SparseVector<Object>::SparseVectorEnumerator::Current()
	{
		return m_pParent->m_elements[*m_current];
		// TODO: return ステートメントをここに挿入します
	}

}
}
