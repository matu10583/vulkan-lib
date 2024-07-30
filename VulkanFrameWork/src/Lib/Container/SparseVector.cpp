#include "Lib/Container/SparseVector.h"

namespace Lib{
namespace Container{
    template<typename Object>
    bool operator==(
        typename SparseVector<Object>::Iterator const&  a,
        typename SparseVector<Object>::Iterator const& b)
    {
        return a.m_itrIdx == b.m_itrIdx;
    }

    template<typename Object>
    bool operator!=(
        typename SparseVector<Object>::Iterator const& a,
        typename SparseVector<Object>::Iterator const& b)
    {
        return a.m_itrIdx != b.m_itrIdx;
    }
}
}
