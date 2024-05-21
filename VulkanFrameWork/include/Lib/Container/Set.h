#pragma once
#include "Lib/Container/RBTree.h"
namespace Lib{
namespace Container{
    template<typename T, class Compare = std::less<T>, typename Allocator = std::allocator<T>>
class Set
:
public Lib::Container::RBTree<T, Compare, Allocator>
{
        public:
        Set();
        ~Set();
};


template<typename T, class Compare, typename Allocator>
inline Set<T, Compare, Allocator>::Set()
{
}

template<typename T, class Compare, typename Allocator>
inline Set<T, Compare, Allocator>::~Set()
{
}

}
}
