#pragma once
#include "Lib/Container/Vector.h"

namespace Lib{
namespace Container{
	template <typename Derived>
	class FilterDispatchable;

	template<typename Object>
class SparseVector
{

public:
	class SparseVectorEnumerator
		:public FilterDispatchable<SparseVectorEnumerator>
	{
	public:
		using value_type = typename SparseVector<Object>::value_type;
		using ArrayIdx = typename SparseVector<Object>::ArrayIdx;
		SparseVectorEnumerator(SparseVector<Object>* _pParent);
		bool MoveNext();
		void Reset();
		value_type& Current();

	private:
		bool m_first;
		int32_t m_counter;
		ArrayIdx const* m_current;
		SparseVector<Object>* m_pParent;
	};
	using SparseID = uint32_t;
	using ArrayIdx = uint32_t;
	using value_type = Object;
	friend class Iterator;
	static const uint32_t GraveMark = UINT32_MAX;

	SparseID Add(Object&& _obj);
	Object* Get(SparseID _id);
	ArrayIdx GetIdx(SparseID _id)const;
	SparseVectorEnumerator GetEnumerator();
	uint32_t Length()const;
	Object const* Data()const;
	Object* Data();
private:
	Lib::Container::Vector<ArrayIdx> m_elemIndices;
	Lib::Container::Vector<Object> m_elements;
};
}
}
#include "Lib/Container/SparseVector.inl"