#pragma once
#include <memory>
#include <functional>
#include <stack>
#include <utility>
#include <stdexcept>

namespace Lib{
namespace Container{
    template<typename T, class Compare = std::less<T>, typename Allocator = std::allocator<T>>
class RBTree
{
public:
    class RBNode;
    class Iterator
    {
    public:
        Iterator();
        Iterator(Iterator const& o);
        friend class RBTree;
        T const operator*()const ;
        T const* operator->()const ;

        friend bool operator==(Iterator const& l, Iterator const& r) {
            if (l.m_isEnd != r.m_isEnd) {
                return false;
            }
            return l.m_pNode == r.m_pNode;
        }
        friend bool operator!=(Iterator const& l, Iterator const& r) {
            if (l.m_isEnd != r.m_isEnd) {
                return true;
            }
            return l.m_pNode != r.m_pNode;
        }

        Iterator& operator++() ;
        Iterator operator++(int i) ;
        Iterator& operator--() ;
        Iterator operator--(int i) ;
    private:
        void Next();
        void Prev();
        RBNode* m_pNode;
        bool m_isEnd;
    };


    class RBNode
    {
        friend class RBTree;
    public:
        RBNode(T const& val);
        RBNode();
        ~RBNode();
        bool IsNil()const;
        void Rotate(bool isClockWise);
        void Connect(RBNode* _pChild, int _chilldPos);
        static RBNode CreateNil();
        int RelativePosFromParent()const;
    private:
        enum class Color
        {
            RED = 0,
            BLACK = 1
        };
        RBNode* m_pParent;
        RBNode* m_pLChild;
        RBNode* m_pRChild;
        T m_Value;
        Color m_color;
        static RBNode m_nil;
    };
        public:
            using allocator_type = typename std::allocator_traits<
                Allocator
            >::template rebind_alloc<RBNode>;
            using alloc_traits = std::allocator_traits<allocator_type>;
        RBTree();
        ~RBTree();
        T* Insert(T const&);
        void Delete(T const&);
        void Clear();
        Iterator Begin();
        Iterator const Begin()const;
        Iterator End();
        Iterator const End()const;
        uint32_t Size()const;
private:
    RBNode* m_pRoot;
    uint32_t m_size;
    void ReColoring(RBNode* _pNode);
    void ReColoringUncleRed(RBNode* _pNode, bool _isParentLeft);
    void ReColoringUncleBlk(RBNode* _pNode, bool _isLeft, bool _isParentLeft);
    RBNode* FindNode(T const& _value)const;
    allocator_type m_allocator;
    void DeleteHasNoTwoChild(RBNode* _node, RBNode* _childNode);
    void DeleteHasTwoChild(RBNode* _node);
    RBNode* ColoringWithRotateBrotherIsRed(RBNode* _node, RBNode* _bro, bool _isNodeLeft);
    RBNode* ColoringWithRotateBrotherIsBlkAndChildBothBlk(RBNode* _node, RBNode* _bro, bool _isNodeLeft);
    RBNode* ColoringWithRotateBrotherIsBlkAndChildLeftRed(RBNode* _node, RBNode* _bro, bool _isNodeLeft);
    RBNode* ColoringWithRotateBrotherIsBlkAndChildRightRed(RBNode* _node, RBNode* _bro, bool _isNodeLeft);
    void ColoringWithRotate(RBNode* _node);
    void Rotate(RBNode* _pNode, bool _clockwise);
    void Connect(RBNode* _pParent, RBNode* _pChild, int _pos);

protected:
    //重複を許す場合は内部カウントを足したりして重複ノードの値を返す
    virtual T* ProcessMultiple(RBNode* _multipleNode){
        return nullptr;
    }
    //例えば重複を許すので内部カウントが0になるまで消したくない、とかの時にオーバーライドしたい
    virtual bool CanDelete(RBNode* _node) { return true; }
};
template<typename T, typename Compare, typename Allocator>
typename RBTree<T, Compare, Allocator>::RBNode RBTree<T, Compare, Allocator>::RBNode::m_nil =
RBTree<T, Compare, Allocator>::RBNode::CreateNil();




template<typename T, class Compare, typename Allocator>
inline RBTree<T, Compare, Allocator>::RBNode::RBNode(T const& val) 
    :m_Value(val)
{
    m_pParent = nullptr;
    m_pLChild = m_pRChild = &m_nil;
    m_color = RBNode::Color::RED;
}

template<typename T, class Compare, typename Allocator>
inline RBTree<T, Compare, Allocator>::RBNode::RBNode()
    :m_Value()
{
    m_pParent = nullptr;
    m_pLChild = m_pRChild = &m_nil;
    m_color = RBNode::Color::RED;
}

template<typename T, typename Compare, typename Allocator>
inline RBTree<T, Compare, Allocator>::RBNode::~RBNode()
{
}

template<typename T, typename Compare, typename Allocator>
inline bool RBTree<T, Compare, Allocator>::RBNode::IsNil() const
{
    return this == &m_nil;
}

template<typename T, typename Compare, typename Allocator>
inline void RBTree<T, Compare, Allocator>::RBNode::Rotate(bool isClockWise)
{
    if (isClockWise) {
        RBNode* pParent = m_pParent;
        RBNode* pLChild = m_pLChild;
        RBNode* pDescendant = pLChild->m_pRChild;

        if (pParent == nullptr) {
            pLChild->m_pParent = nullptr;
        }
        else if (pParent->m_pLChild == this) {
            pParent->Connect(pLChild, -1);
        }
        else {
            pParent->Connect(pLChild, 1);
        }

        pLChild->Connect(this, 1);

        Connect(pDescendant, -1);
    }
    else {
        RBNode* pParent = m_pParent;
        RBNode* pRChild = m_pRChild;
        RBNode* pDescendant = pRChild->m_pLChild;

        if (pParent == nullptr) {
            pRChild->m_pParent = nullptr;
        }
        else if (pParent->m_pLChild == this) {
            pParent->Connect(pRChild, -1);
        }
        else {
            pParent->Connect(pRChild, 1);
        }

        pRChild->Connect(this, -1);

        Connect(pDescendant, 1);
    }

}

template<typename T, typename Compare, typename Allocator>
inline void RBTree<T, Compare, Allocator>::RBNode::Connect(RBNode* _pChild, int _chilldPos)
{
    if (_chilldPos == -1) {
        m_pLChild = _pChild;
    }
    else if(_chilldPos == 1) {
        m_pRChild = _pChild;
    }
    else {
        return;
    }
    if (_pChild->IsNil()) return;
    _pChild->m_pParent = this;
}

template<typename T, class Compare, typename Allocator>
inline typename RBTree<T, Compare, Allocator>::RBNode RBTree<T, Compare, Allocator>::RBNode::CreateNil()
{
    auto ret = RBNode();
    ret.m_color = Color::BLACK;
    return ret;
}

template<typename T, class Compare, typename Allocator>
inline int RBTree<T, Compare, Allocator>::RBNode::RelativePosFromParent() const
{
    if (m_pParent == nullptr) {
        return 0;
    }
    if (m_pParent->m_pLChild == this) return -1;
    if (m_pParent->m_pRChild == this) return 1;
    return 0;
}

template<typename T, typename Compare, typename Allocator>
inline RBTree<T, Compare, Allocator>::RBTree()
{
    m_pRoot = &(RBNode::m_nil);
    m_size = 0;
}

template<typename T, typename Compare, typename Allocator>
inline RBTree<T, Compare, Allocator>::~RBTree()
{
    //TODO: all delete
    Clear();
}

template<typename T, typename Compare, typename Allocator>
inline T* RBTree<T, Compare, Allocator>::Insert(T const& val)
{
    RBNode* pChild = m_pRoot;
    RBNode* pParent = nullptr;
    bool isLess = false;
    while (!pChild->IsNil())
    {
        pParent = pChild;
        isLess = Compare()((val), (pParent->m_Value));
        if (isLess) {
            pChild = pParent->m_pLChild;
        }
        else {
            if (val == pParent->m_Value) {
                return ProcessMultiple(pParent);
            }
            pChild = pParent->m_pRChild;
        }
    }

    RBNode* pAddedNode = alloc_traits::allocate(m_allocator, 1);
    alloc_traits::construct(m_allocator, pAddedNode, val);
    m_size++;
    if (pParent == nullptr) {
        m_pRoot = pAddedNode;
        m_pRoot->m_color = RBNode::Color::BLACK;
    }
    else {
        Connect(pParent, pAddedNode, (isLess)?-1:1);
    }

    ReColoring(pAddedNode);

    return &pAddedNode->m_Value;
}

template<typename T, class Compare, typename Allocator>
inline void RBTree<T, Compare, Allocator>::Delete(T const& _val)
{
    RBNode* pTarget = FindNode(_val);
    if (pTarget->IsNil()) return;
    if (!CanDelete(pTarget)) return;

    RBNode* pRNode = pTarget->m_pRChild;
    RBNode* pLNode = pTarget->m_pLChild;
    if (!pRNode->IsNil() && !pLNode->IsNil()) {
        DeleteHasTwoChild(pTarget);
    }
    else {
        DeleteHasNoTwoChild(pTarget,
            (!pRNode->IsNil()) ? pRNode : pLNode);
    }
    //free
    m_size--;
    alloc_traits::destroy(m_allocator, pTarget);
    alloc_traits::deallocate(m_allocator, pTarget, 1);
}

template<typename T, class Compare, typename Allocator>
inline void RBTree<T, Compare, Allocator>::Clear()
{
    std::stack<RBNode*> delstack;
    delstack.push(m_pRoot);
    while (!delstack.empty())
    {
        RBNode* pDel = delstack.top();
        if (pDel->IsNil()) break;
        if (!pDel->m_pLChild->IsNil()) {
            delstack.push(pDel->m_pLChild);
        }
        else if (!pDel->m_pRChild->IsNil()) {
            delstack.push(pDel->m_pRChild);
        }
        else {
            int pos = pDel->RelativePosFromParent();
            if (pos == -1) {
                pDel->m_pParent->m_pLChild = &(pDel->m_nil);
            }
            else if (pos == 1) {
                pDel->m_pParent->m_pRChild = &(pDel->m_nil);
            }
            alloc_traits::destroy(m_allocator, pDel);
            alloc_traits::deallocate(m_allocator, pDel, 1);
            delstack.pop();
        }

    }
    m_size = 0;
}

template<typename T, class Compare, typename Allocator>
inline typename RBTree<T, Compare, Allocator>::Iterator RBTree<T, Compare, Allocator>::Begin()
{
    Iterator ret{};
    if (m_pRoot->IsNil()) {
        ret.m_pNode = nullptr;
    }
    else {
        ret.m_pNode = m_pRoot;
        while (true)
        {
            if (!ret.m_pNode->m_pLChild->IsNil()) {
                ret.m_pNode = ret.m_pNode->m_pLChild;
            }
            else {
                break;
            }
        }
    }
    return ret;
}
template<typename T, class Compare, typename Allocator>
inline typename RBTree<T, Compare, Allocator>::Iterator const RBTree<T, Compare, Allocator>::Begin()const
{
    Iterator ret{};
    if (m_pRoot->IsNil()) {
        ret.m_pNode = nullptr;
    }
    else {
        ret.m_pNode = m_pRoot;
        while (true)
        {
            if (!ret.m_pNode->m_pLChild->IsNil()) {
                ret.m_pNode = ret.m_pNode->m_pLChild;
            }
            else {
                break;
            }
        }
    }
    return ret;
}

template<typename T, class Compare, typename Allocator>
inline typename RBTree<T, Compare, Allocator>::Iterator RBTree<T, Compare, Allocator>::End()
{
    Iterator ret{};
    ret.m_isEnd = true;
    if (m_pRoot->IsNil()) {
        ret.m_pNode = nullptr;
    }
    else {
        ret.m_pNode = m_pRoot;
        while (true)
        {
            if (!ret.m_pNode->m_pRChild->IsNil()) {
                ret.m_pNode = ret.m_pNode->m_pRChild;
            }
            else {
                break;
            }
        }
    }
    return ret;
}
template<typename T, class Compare, typename Allocator>
inline typename RBTree<T, Compare, Allocator>::Iterator const RBTree<T, Compare, Allocator>::End()const
{
    Iterator ret{};
    ret.m_isEnd = true;
    if (m_pRoot->IsNil()) {
        ret.m_pNode = nullptr;
    }
    else {
        ret.m_pNode = m_pRoot;
        while (true)
        {
            if (!ret.m_pNode->m_pRChild->IsNil()) {
                ret.m_pNode = ret.m_pNode->m_pRChild;
            }
            else {
                break;
            }
        }
    }
    return ret;
}

template<typename T, class Compare, typename Allocator>
inline uint32_t RBTree<T, Compare, Allocator>::Size() const
{
    return m_size;
}

template<typename T, typename Compare, typename Allocator>
inline void RBTree<T, Compare, Allocator>::ReColoring(RBNode* _pNode)
{
    RBNode* pParent = _pNode->m_pParent;
    if (pParent == nullptr) {
        _pNode->m_color = RBNode::Color::BLACK;
        return;
    }
    if (pParent->m_color == RBNode::Color::BLACK) {
        return;
    }
    RBNode* pGrandpa = pParent->m_pParent;
    bool isParentLeft = pGrandpa->m_pLChild == pParent;
    RBNode* pUncle = pGrandpa->m_pLChild;
    if (isParentLeft) {
        pUncle = pGrandpa->m_pRChild;
    }
    if (pUncle->m_color == RBNode::Color::RED) {
        ReColoringUncleRed(_pNode, isParentLeft);
    }
    else if (pUncle->m_color == RBNode::Color::BLACK) {
        bool isLeft = pParent->m_pLChild == _pNode;
        ReColoringUncleBlk(_pNode, isLeft, isParentLeft);
    }
}

template<typename T, typename Compare, typename Allocator>
inline void RBTree<T, Compare, Allocator>::ReColoringUncleRed(RBNode* _pNode, bool _isParentLeft)
{
    RBNode* pGrandpa = _pNode->m_pParent->m_pParent;
    pGrandpa->m_color = RBNode::Color::RED;
    pGrandpa->m_pLChild->m_color = pGrandpa->m_pRChild->m_color = RBNode::Color::BLACK;
    ReColoring(pGrandpa);
}

template<typename T, typename Compare, typename Allocator>
inline void RBTree<T, Compare, Allocator>::ReColoringUncleBlk(RBNode* _pNode, bool _isLeft, bool _isParentLeft)
{
    RBNode* pParent = _pNode->m_pParent;
    RBNode* pGrandpa = pParent->m_pParent;
    if (_isLeft != _isParentLeft) {
        Rotate(pParent, _isLeft);
    }

    Rotate(pGrandpa, _isParentLeft);
    pGrandpa->m_color = RBNode::Color::RED;
    pGrandpa->m_pParent->m_color = RBNode::Color::BLACK;
}

template<typename T, class Compare, typename Allocator>
inline typename RBTree<T, Compare, Allocator>::RBNode* RBTree<T, Compare, Allocator>::FindNode(T const& _value) const
{
    RBNode* result = nullptr;
    RBNode* nowNode = m_pRoot;
    while (!nowNode->IsNil())
    {
        if (nowNode->m_Value == _value) {
            result = nowNode;
            break;
        }
        bool isless = Compare()(_value, nowNode->m_Value);
        if (isless) {
            nowNode = nowNode->m_pLChild;
        }
        else {
            nowNode = nowNode->m_pRChild;
        }
    }
    return result;
}

template<typename T, class Compare, typename Allocator>
inline void RBTree<T, Compare, Allocator>::DeleteHasNoTwoChild(RBNode* _node, RBNode* _pChildNode)
{
    int pos = _node->RelativePosFromParent();

    RBNode* pParent = _node->m_pParent;
    Connect(pParent, _pChildNode, pos);
    //この時、削除ノードの子ノードの数は0,1個である
    
    //子ノードが1この場合、その子ノードは必ず赤ノードである。なぜなら黒ノードの場合は兄弟木が黒制約に違反するため
    //つまり削除ノードの色に合わせれば制約は保存される
    if (!_pChildNode->IsNil()) {
        _pChildNode->m_color = _node->m_color;
    }
    //子ノードが0個の場合、そこの部分木が消滅するので問題ない
}

template<typename T, class Compare, typename Allocator>
inline void RBTree<T, Compare, Allocator>::DeleteHasTwoChild(RBNode* _node)
{
    RBNode* pNearestLargerNode = _node->m_pRChild;
    bool isNearestLargerNodeChild = true;
    while (!(pNearestLargerNode->m_pLChild->IsNil())) {
        pNearestLargerNode = pNearestLargerNode->m_pLChild;
        isNearestLargerNodeChild = false;
    }
    RBNode* xNode = pNearestLargerNode->m_pRChild;
    //入れ替え
    if (isNearestLargerNodeChild) {
        Connect(_node->m_pParent, pNearestLargerNode, _node->RelativePosFromParent());
    }
    else {
        //次に大きいノードを木から外す
        RBNode* pNearestLargerParent = pNearestLargerNode->m_pParent;
        Connect(pNearestLargerParent, pNearestLargerNode->m_pRChild, -1);
        //消すノードと次に大きいノードの入れ替え
        int pos = _node->RelativePosFromParent();
        RBNode* pParent = _node->m_pParent;
        Connect(pParent, pNearestLargerNode, pos);
        Connect(pNearestLargerNode, _node->m_pRChild, 1);
        Connect(pNearestLargerNode, _node->m_pLChild, -1);
    }
    //色分け
    //このパターンでは消されるノードは他ノードに置き換えられているので実質消されたノードというのは置き換えられている次に大きいノードと言える
    auto deletedColor = pNearestLargerNode->m_color;
    pNearestLargerNode->m_color = _node->m_color;
    if (deletedColor == RBNode::Color::BLACK) {
        ColoringWithRotate(xNode);
    }
}

template<typename T, class Compare, typename Allocator>
inline typename RBTree<T, Compare, Allocator>::RBNode* RBTree<T, Compare, Allocator>::ColoringWithRotateBrotherIsRed(RBNode* _node, RBNode* _bro, bool _isNodeLeft)
{
    RBNode* pParent = _node->m_pParent;
    std::swap(pParent->m_color, _bro->m_color);
    Rotate(pParent, !_isNodeLeft);
    return _node;
}

template<typename T, class Compare, typename Allocator>
inline typename RBTree<T, Compare, Allocator>::RBNode* RBTree<T, Compare, Allocator>::ColoringWithRotateBrotherIsBlkAndChildBothBlk(RBNode* _node, RBNode* _bro, bool _isNodeLeft)
{
    _bro->m_color = RBNode::Color::RED;
    return _bro;
}

template<typename T, class Compare, typename Allocator>
inline typename RBTree<T, Compare, Allocator>::RBNode* RBTree<T, Compare, Allocator>::ColoringWithRotateBrotherIsBlkAndChildLeftRed(RBNode* _node, RBNode* _bro, bool _isNodeLeft)
{
    std::swap(_bro->m_color, _bro->m_pLChild->m_color);
    Rotate(_bro, _isNodeLeft);
    return _node;
}

template<typename T, class Compare, typename Allocator>
inline typename RBTree<T, Compare, Allocator>::RBNode* RBTree<T, Compare, Allocator>::ColoringWithRotateBrotherIsBlkAndChildRightRed(RBNode* _node, RBNode* _bro, bool _isNodeLeft)
{
    std::swap(_bro->m_pParent->m_color, _bro->m_color);
    _bro->m_pRChild->m_color = RBNode::Color::BLACK;
    Rotate(_node->m_pParent, !_isNodeLeft);
    return m_pRoot;
}

template<typename T, class Compare, typename Allocator>
inline void RBTree<T, Compare, Allocator>::ColoringWithRotate(RBNode* _node)
{
    while (m_pRoot != _node && _node->m_color == RBNode::Color::BLACK)
    {
        bool isLeft = (_node->RelativePosFromParent() == -1);
        RBNode* bro = (isLeft) ? _node->m_pParent->m_pRChild : _node->m_pParent->m_pLChild;
        if (bro->m_color == RBNode::Color::RED) {
            _node = ColoringWithRotateBrotherIsRed(_node, bro, isLeft);
        }
        else {
            if (bro->m_pRChild->m_color == RBNode::Color::RED) {
                _node = ColoringWithRotateBrotherIsBlkAndChildRightRed(_node, bro, isLeft);
            }
            else if (bro->m_pLChild->m_color == RBNode::Color::RED) {
                _node = ColoringWithRotateBrotherIsBlkAndChildLeftRed(_node, bro, isLeft);
            }
            else {
                _node = ColoringWithRotateBrotherIsBlkAndChildBothBlk(_node, bro, isLeft);
            }
        }
    }
    //_nodeが赤の場合はこれを黒に変えれば数が合う。もともと黒ならこの操作は意味をなさない
    _node->m_color = RBNode::Color::BLACK;
}

template<typename T, class Compare, typename Allocator>
inline void RBTree<T, Compare, Allocator>::Rotate(RBNode* _pNode, bool _clockwise)
{
    if (_pNode == m_pRoot) {
        m_pRoot = (_clockwise) ? _pNode->m_pLChild : _pNode->m_pRChild;
    }
    _pNode->Rotate(_clockwise);
}

template<typename T, class Compare, typename Allocator>
inline void RBTree<T, Compare, Allocator>::Connect(RBNode* _pParent, RBNode* _pChild, int _pos)
{
    if (_pParent == nullptr) {
        m_pRoot = _pChild;
        m_pRoot->m_pParent = nullptr;
        return;
    }
    _pParent->Connect(_pChild, _pos);
}




template<typename T, class Compare, typename Allocator>
inline void RBTree<T, Compare, Allocator>::Iterator::Next()
{        
    RBNode* prev = m_pNode;
    //増える方向へ移動
    if (!m_pNode->m_pRChild->IsNil()) {
        //右に降りれるならそれで終わり
        m_pNode = m_pNode->m_pRChild;
        //左に行けなくなるまで行く
        while (true) {
            if (!m_pNode->m_pLChild->IsNil()) {
                break;
            }
            m_pNode = m_pNode->m_pLChild;
        }
        m_isEnd = false;
        return;
    }
    //降りる方向に増えるノードはない。親をさかのぼる
    while (true)
    {
        if (m_pNode->m_pParent == nullptr) {
            //ルートノードまで返ってきたので終わり
            if (m_isEnd) {
                //end状態からさらに進もうとしている
                throw std::out_of_range("もう進めない");
            }
            m_pNode = prev;
            m_isEnd = true;
            return;
        }
        int pos = m_pNode->RelativePosFromParent();
        m_pNode = m_pNode->m_pParent;
        if (pos == -1) {
            //増える方向に行っているかつ今のノードとの値の間になるノードはない
            m_isEnd = false;
            return;
        }
    }


}

template<typename T, class Compare, typename Allocator>
inline void RBTree<T, Compare, Allocator>::Iterator::Prev()
{
    if (m_isEnd) {//実際は直感に合わない状況もあるだろうが、Endからさかのぼっていくこと自体まれだと思うのでこの実装で
        m_isEnd = false;
        return;
    }
    //減る方向へ移動
    if (!m_pNode->m_pLChild->IsNil()) {
        //左に降りれるならそれで終わり
        m_pNode = m_pNode->m_pLChild;
        //右に行けなくなるまで行く
        while (true) {
            if (!m_pNode->m_pRChild->IsNil()) {
                break;
            }
            m_pNode = m_pNode->m_pRChild;
        }
        return;
    }
    //降りる方向に減るノードはない。親をさかのぼる
    while (true)
    {
        if (m_pNode->m_pParent == nullptr) {
            //ルートノードまで返ってきたので終わり
            throw std::out_of_range("これ以上戻れません");
        }
        int pos = m_pNode->RelativePosFromParent();
        m_pNode = m_pNode->m_pParent;
        if (pos == 1) {
            //減る方向に行っているかつ今のノードとの値の間になるノードはない
            return;
        }
    }
}

template<typename T, class Compare, typename Allocator>
inline RBTree<T, Compare, Allocator>::Iterator::Iterator()
    :m_pNode(nullptr)
    ,m_isEnd(false)
{
}

template<typename T, class Compare, typename Allocator>
inline RBTree<T, Compare, Allocator>::Iterator::Iterator(Iterator const& o)
    :m_pNode(o.m_pNode)
    ,m_isEnd(o.m_isEnd)
{

}

template<typename T, class Compare, typename Allocator>
inline T const RBTree<T, Compare, Allocator>::Iterator::operator*() const
{
    if (m_isEnd) {
        std::runtime_error("Endにアクセスしている");
    }
    return m_pNode->m_Value;
}

template<typename T, class Compare, typename Allocator>
inline T const* RBTree<T, Compare, Allocator>::Iterator::operator->() const
{
    if (m_isEnd) {
        return nullptr;
    }
    return &(m_pNode->m_Value);
}

template<typename T, class Compare, typename Allocator>
inline typename RBTree<T, Compare, Allocator>::Iterator& RBTree<T, Compare, Allocator>::Iterator::operator++()
{
    Next();
    return *this;
}

template<typename T, class Compare, typename Allocator>
inline typename RBTree<T, Compare, Allocator>::Iterator RBTree<T, Compare, Allocator>::Iterator::operator++(int i)
{
    Next();
    return *this;
}

template<typename T, class Compare, typename Allocator>
inline typename RBTree<T, Compare, Allocator>::Iterator& RBTree<T, Compare, Allocator>::Iterator::operator--()
{
    Prev();
    return *this;
}

template<typename T, class Compare, typename Allocator>
inline typename RBTree<T, Compare, Allocator>::Iterator RBTree<T, Compare, Allocator>::Iterator::operator--(int i)
{
    Prev();
    return *this;
}



}
}
