#ifndef VTREE_H
#define VTREE_H

#include <algorithm>
#include <cassert>
#include <vector>

namespace NSLibrary {

template<class T>
class CVTreeNode {
public:
  using CData = T;
  using CIndex = int64_t;
  static constexpr CIndex kRootIndex = 0;
  static constexpr CIndex kUndefined = -1;

  CVTreeNode() = default;

  CVTreeNode(const CData& Data, CIndex DistanceToRoot)
      : Data_(Data), NumberOfChildren_(0), DistanceToRoot_(DistanceToRoot) {
  }
  CVTreeNode(CData&& Data, CIndex DistanceToRoot)
      : Data_(std::move(Data)), NumberOfChildren_(0),
        DistanceToRoot_(DistanceToRoot) {
  }

  bool hasChildren() const {
    return NumberOfChildren_ != 0;
  }

  CData& data() {
    return Data_;
  }
  const CData& data() const {
    return Data_;
  }
  CIndex& parentIndex() {
    return ParentIndex_;
  }
  CIndex parentIndex() const {
    return ParentIndex_;
  }
  CIndex& firstChildIndex() {
    return FirstChildIndex_;
  }
  CIndex firstChildIndex() const {
    return FirstChildIndex_;
  }
  CIndex& lastChildIndex() {
    return LastChildIndex_;
  }
  CIndex lastChildIndex() const {
    return LastChildIndex_;
  }
  CIndex& previousSiblingIndex() {
    return PreviousSiblingIndex_;
  }
  CIndex previousSiblingIndex() const {
    return PreviousSiblingIndex_;
  }
  CIndex& nextSiblingIndex() {
    return NextSiblingIndex_;
  }
  CIndex nextSiblingIndex() const {
    return NextSiblingIndex_;
  }
  CIndex& numberOfChildren() {
    return NumberOfChildren_;
  }
  CIndex numberOfChildren() const {
    return NumberOfChildren_;
  }
  CIndex& distanceToRoot() {
    return DistanceToRoot_;
  }
  CIndex distanceToRoot() const {
    return DistanceToRoot_;
  }

  template<class TOut>
  friend TOut& operator<<(TOut& out, const CVTreeNode& node) {
    out << "[data = " << node.Data_ << ", parent = " << node.ParentIndex_
        << ", f child = " << node.FirstChildIndex_
        << ", l child = " << node.LastChildIndex_
        << ", p sibl = " << node.PreviousSiblingIndex_
        << ", n sibl = " << node.NextSiblingIndex_
        << ", numb children = " << node.NumberOfChildren_
        << ", dist to root = " << node.DistanceToRoot_ << "]";
    return out;
  }

private:
  CData Data_{};
  CIndex ParentIndex_ = kUndefined;
  CIndex FirstChildIndex_ = kUndefined;
  CIndex LastChildIndex_ = kUndefined;
  CIndex PreviousSiblingIndex_ = kUndefined;
  CIndex NextSiblingIndex_ = kUndefined;
  CIndex NumberOfChildren_ = 0;
  CIndex DistanceToRoot_ = 0;
};

// The vertices of the tree are stored in a vector.
// The class invariants:
// 1) the root is always the first element of the vector
// 2) all elements are sorted with respect to the following order
// vertexr -> subtrees from left to right
// Formally:
// a) the root of each subtree is before each element of the subtree
// b) children are compared left to right
// c) each vertex of the subtree of a smaller child is less than
// any vertex of the subtree of a greater child.
template<class TType>
class CVTree {
public:
  using CNode = CVTreeNode<TType>;
  // I have to define several types and constants explicitely
  // otherwise I have a compilation error

  using CData = typename CNode::CData;
  using CIndex = typename CNode::CIndex;
  using CVTreeBase = std::vector<CNode>;

  static constexpr CIndex kRootIndex = CNode::kRootIndex;
  static constexpr CIndex kUndefined = CNode::kUndefined;

  CVTree() = default;
  explicit CVTree(const CData& Data) {
    TreeBase_.emplace_back(Data, 0);
  }
  explicit CVTree(CData&& Data) {
    TreeBase_.emplace_back(std::move(Data), 0);
  }

  void destroyExceptRoot() {
    if (empty())
      return;
    TreeBase_.resize(1);
    firstChildIndex(kRootIndex) = kUndefined;
    lastChildIndex(kRootIndex) = kUndefined;
    numberOfChildren(kRootIndex) = 0;
    assert(previousSiblingIndex_(kRootIndex) == kUndefined);
    assert(nextSiblingIndex_(kRootIndex) == kUndefined);
    assert(parentIndex_(kRootIndex) == kUndefined);
    assert(distanceToRoot_(kRootIndex) == 0);
  }

  bool empty() const {
    return TreeBase_.empty();
  }
  CIndex size() const {
    return TreeBase_.size();
  }
  void clear() {
    TreeBase_.clear();
  }

protected:
  bool isCorrect_(CIndex Index) const {
    return 0 <= Index && size_t(Index) < TreeBase_.size();
  }

  const CData& data_(CIndex Index) const {
    return TreeBase_[Index].data();
  }
  CIndex parentIndex_(CIndex Index) const {
    return TreeBase_[Index].parentIndex();
  }
  CIndex firstChildIndex_(CIndex Index) const {
    return TreeBase_[Index].firstChildIndex();
  }
  CIndex lastChildIndex_(CIndex Index) const {
    return TreeBase_[Index].lastChildIndex();
  }
  CIndex previousSiblingIndex_(CIndex Index) const {
    return TreeBase_[Index].previousSiblingIndex();
  }
  CIndex nextSiblingIndex_(CIndex Index) const {
    return TreeBase_[Index].nextSiblingIndex();
  }
  CIndex numberOfChildren_(CIndex Index) const {
    return TreeBase_[Index].numberOfChildren();
  }
  CIndex distanceToRoot_(CIndex Index) const {
    return TreeBase_[Index].distanceToRoot();
  }

  // ?? Do I need to open this??
public:
  const CData& data(CIndex Index) const {
    assert(isCorrect_(Index));
    return TreeBase_[Index].data();
  }
  CData& data(CIndex Index) {
    assert(isCorrect_(Index));
    return TreeBase_[Index].data();
  }
  CIndex parentIndex(CIndex Index) const {
    assert(isCorrect_(Index));
    return TreeBase_[Index].parentIndex();
  }
  CIndex& parentIndex(CIndex Index) {
    assert(isCorrect_(Index));
    return TreeBase_[Index].parentIndex();
  }
  CIndex firstChildIndex(CIndex Index) const {
    assert(isCorrect_(Index));
    return TreeBase_[Index].firstChildIndex();
  }
  CIndex& firstChildIndex(CIndex Index) {
    assert(isCorrect_(Index));
    return TreeBase_[Index].firstChildIndex();
  }
  CIndex lastChildIndex(CIndex Index) const {
    assert(isCorrect_(Index));
    return TreeBase_[Index].lastChildIndex();
  }
  CIndex& lastChildIndex(CIndex Index) {
    assert(isCorrect_(Index));
    return TreeBase_[Index].lastChildIndex();
  }
  CIndex previousSiblingIndex(CIndex Index) const {
    assert(isCorrect_(Index));
    return TreeBase_[Index].previousSiblingIndex();
  }
  CIndex& previousSiblingIndex(CIndex Index) {
    assert(isCorrect_(Index));
    return TreeBase_[Index].previousSiblingIndex();
  }
  CIndex nextSiblingIndex(CIndex Index) const {
    assert(isCorrect_(Index));
    return TreeBase_[Index].nextSiblingIndex();
  }
  CIndex& nextSiblingIndex(CIndex Index) {
    assert(isCorrect_(Index));
    return TreeBase_[Index].nextSiblingIndex();
  }
  CIndex numberOfChildren(CIndex Index) const {
    assert(isCorrect_(Index));
    return TreeBase_[Index].numberOfChildren();
  }
  CIndex& numberOfChildren(CIndex Index) {
    assert(isCorrect_(Index));
    return TreeBase_[Index].numberOfChildren();
  }
  CIndex distanceToRoot(CIndex Index) const {
    assert(isCorrect_(Index));
    return TreeBase_[Index].distanceToRoot();
  }
  CIndex& distanceToRoot(CIndex Index) {
    assert(isCorrect_(Index));
    return TreeBase_[Index].distanceToRoot();
  }

protected:
  bool hasParent_(CIndex Index) const {
    return parentIndex_(Index) != kUndefined;
  }
  bool hasFirstChild_(CIndex Index) const {
    return firstChildIndex_(Index) != kUndefined;
  }
  bool hasLastChild_(CIndex Index) const {
    return lastChildIndex_(Index) != kUndefined;
  }
  bool hasPreviousSibling_(CIndex Index) const {
    return previousSiblingIndex_(Index) != kUndefined;
  }
  bool hasNextSibling_(CIndex Index) const {
    return nextSiblingIndex_(Index) != kUndefined;
  }

  bool isRoot_(CIndex Index) const {
    return Index == kRootIndex;
  }
  bool hasChildren_(CIndex Index) const {
    return numberOfChildren_(Index) != 0;
  }

protected:
  class CConstIteratorDefines {
  public:
    using value_type = const CData;
    using difference_type = int64_t;
    using pointer = value_type*;
    using reference = value_type&;
    using CIndex = CIndex;
    using CNode = const CNode;
    using CHostTreePtr = const CVTree<CData>*;
    using CNodeRef = CNode&;

  protected:
    ~CConstIteratorDefines() = default;
  };

  class CIteratorDefines {
  public:
    using value_type = CData;
    using difference_type = int64_t;
    using pointer = value_type*;
    using reference = value_type&;
    using CIndex = CIndex;
    using CNode = CNode;
    using CHostTreePtr = CVTree<CData>*;
    using CNodeRef = CNode&;

  protected:
    ~CIteratorDefines() = default;
  };

  template<class TIteratorDefines>
  friend class CBaseIterator;

  template<class TIteratorDefines>
  class CBaseIterator : public TIteratorDefines {
  public:
    template<class TOtherIteratorDefines>
    friend class CBaseIterator;

    using value_type = typename TIteratorDefines::value_type;
    using difference_type = typename TIteratorDefines::difference_type;
    using pointer = typename TIteratorDefines::pointer;
    using reference = typename TIteratorDefines::reference;
    using CIndex = typename TIteratorDefines::CIndex;
    using CHostTreePtr = typename TIteratorDefines::CHostTreePtr;
    using CNode = typename TIteratorDefines::CNode;

    CBaseIterator() = default;
    CBaseIterator(CHostTreePtr HostTree, CIndex Current)
        : Host_(HostTree), Current_(Current) {
    }
    CBaseIterator(const CBaseIterator& other) = default;
    CBaseIterator(CBaseIterator&& other) noexcept
        : Host_(std::move(other.Host_)), Current_(std::move(other.Current_)) {
      other.Host_ = nullptr;
      other.Current_ = kUndefined;
    }
    CBaseIterator& operator=(const CBaseIterator& other) = default;
    CBaseIterator& operator=(CBaseIterator&& other) noexcept {
      Host_ = std::move(other.Host_);
      Current_ = std::move(other.Current_);
      other.Host_ = nullptr;
      other.Current_ = kUndefined;
      return *this;
    }

    template<class TIterDefs>
    bool operator==(const CBaseIterator<TIterDefs>& Iterator) const {
      return Host_ == Iterator.Host_ && Current_ == Iterator.Current_;
    }
    template<class TIterDefs>
    bool operator!=(const CBaseIterator<TIterDefs>& Iterator) const {
      return !(*this == Iterator);
    }

    bool isDefined() const {
      return isHostDefined_() && isCorrect_();
    }
    bool isRoot() const {
      return isHostDefined_() && Host_->isRoot_(Current_);
    }
    bool isLeaf() const {
      return isHostDefined_() && isCorrect_() && !Host_->hasChildren_(Current_);
    }
    bool hasParent() const {
      return isHostDefined_() && isCorrect_() && Host_->hasParent_(Current_);
    }
    bool hasChildren() const {
      return isHostDefined_() && isCorrect_() && Host_->hasChildren_(Current_);
    }
    bool hasNextSibling() const {
      return isHostDefined_() && isCorrect_() &&
             Host_->hasNextSibling_(Current_);
    }
    bool hasPreviousSibling() const {
      return isHostDefined_() && isCorrect_() &&
             Host_->hasPreviousSibling_(Current_);
    }

    CIndex getNumberOfChildren() const {
      if (isDefined())
        return Host_->numberOfChildren_(Current_);
      return 0;
    }
    CIndex getSizeOfSubTree() const {
      if (!isDefined())
        return 0;
      return getSubTreeEndHandler() - Current_;
    }
    CIndex getNumberOfSiblings() const {
      if (!hasParent())
        return 0;
      return Host_->numberOfChildren_(Host_->parentIndex(Current_)) - 1;
    }
    CIndex getLengthOfSubTree() const {
      if (!isDefined())
        return 0;
      CIndex EndHandler = getSubTreeEndHandler();
      CIndex MaxDistanceToRoot = 0;
      for (CIndex Current = Current_; Current != EndHandler; ++Current)
        MaxDistanceToRoot =
            std::max(MaxDistanceToRoot, Host_->distanceToRoot(Current));
      return MaxDistanceToRoot - Host_->distanceToRoot(Current_) + 1;
    }
    CIndex getNumberOfLeaves() const {
      if (!isDefined())
        return 0;
      CIndex EndHandler = getSubTreeEndHandler();
      CIndex NumberOfLeaves = 0;
      for (CIndex Current = Current_; Current != EndHandler; ++Current)
        if (Host_->hasChildren_(Current))
          ++NumberOfLeaves;
      assert(NumberOfLeaves > 0);
      return NumberOfLeaves;
    }
    CIndex getDistanceToRoot() const {
      if (!isDefined())
        return 0;
      return Host_->distanceToRoot(Current_);
    }
    CIndex getHostSize() const {
      if (!isDefined())
        return 0;
      return Host_->size();
    }

    void setToParent() {
      assert(hasParent());
      Current_ = parentIndex_();
    }
    void setToFirstChild() {
      assert(hasChildren());
      Current_ = firstChildIndex_();
    }
    void setToLastChild() {
      assert(hasChildren());
      Current_ = lastChildIndex_();
    }
    void setToNextSibling() {
      assert(hasNextSibling());
      Current_ = nextSiblingIndex_();
    }
    void setToPreviousSibling() {
      assert(hasPreviousSibling());
      Current_ = previousSiblingIndex_();
    }

    void addLastChild(const value_type& NodeData) {
      assert(!hasNextSibling());
      CIndex NewNodePosition = getHostSize();
      (Host_->TreeBase_).emplace_back(NodeData, getDistanceToRoot() + 1);
      if (isLeaf()) {
        firstChildIndex() = NewNodePosition;
        lastChildIndex() = NewNodePosition;
        Host_->parentIndex(NewNodePosition) = Current_;
      } else {
        Host_->nextSiblingIndex(lastChildIndex_()) = NewNodePosition;
        Host_->previousSiblingIndex(NewNodePosition) = lastChildIndex_();
        Host_->parentIndex(NewNodePosition) = Current_;
        lastChildIndex() = NewNodePosition;
      }
      ++numberOfChildren();
    }
    void addLastChild(value_type&& NodeData) {
      assert(!hasNextSibling());
      CIndex NewNodePosition = getHostSize();
      (Host_->TreeBase_)
          .emplace_back(std::move(NodeData), getDistanceToRoot() + 1);
      if (isLeaf()) {
        firstChildIndex() = NewNodePosition;
        lastChildIndex() = NewNodePosition;
        Host_->parentIndex(NewNodePosition) = Current_;
      } else {
        Host_->nextSiblingIndex(lastChildIndex_()) = NewNodePosition;
        Host_->previousSiblingIndex(NewNodePosition) = lastChildIndex_();
        Host_->parentIndex(NewNodePosition) = Current_;
        lastChildIndex() = NewNodePosition;
      }
      ++numberOfChildren();
    }

    //    void changeHost(CHostTreePtr Host) {
    //      Host_ = Host;
    //    }

  protected:
    bool isHostDefined_() const {
      return Host_ != nullptr;
    }
    bool isCurrentInFullRange_() const {
      return 0 <= Current_ && Current_ <= Host_->size();
    }
    bool isCorrect_() const {
      return Host_->isCorrect_(Current_);
    }

    CIndex parentIndex() const {
      return Host_->parentIndex(Current_);
    }
    CIndex& parentIndex() {
      return Host_->parentIndex(Current_);
    }
    CIndex firstChildIndex() const {
      return Host_->firstChildIndex(Current_);
    }
    CIndex& firstChildIndex() {
      return Host_->firstChildIndex(Current_);
    }
    CIndex lastChildIndex() const {
      return Host_->lastChildIndex(Current_);
    }
    CIndex& lastChildIndex() {
      return Host_->lastChildIndex(Current_);
    }
    CIndex previousSiblingIndex() const {
      return Host_->previousSiblingIndex(Current_);
    }
    CIndex& previousSiblingIndex() {
      return Host_->previousSiblingIndex(Current_);
    }
    CIndex nextSiblingIndex() const {
      return Host_->nextSiblingIndex(Current_);
    }
    CIndex& nextSiblingIndex() {
      return Host_->nextSiblingIndex(Current_);
    }

    CIndex parentIndex_() const {
      return Host_->parentIndex(Current_);
    }
    CIndex firstChildIndex_() const {
      return Host_->firstChildIndex(Current_);
    }
    CIndex lastChildIndex_() const {
      return Host_->lastChildIndex(Current_);
    }
    CIndex previousSiblingIndex_() const {
      return Host_->previousSiblingIndex(Current_);
    }
    CIndex nextSiblingIndex_() const {
      return Host_->nextSiblingIndex(Current_);
    }

    CIndex numberOfChildren() const {
      return Host_->numberOfChildren(Current_);
    }
    CIndex& numberOfChildren() {
      return Host_->numberOfChildren(Current_);
    }

    CIndex getSubTreeEndHandler() const {
      CBaseIterator Current(*this);
      while (!Current.isRoot() && !Current.hasNextSibling())
        Current.setToParent();
      if (Current.hasNextSibling())
        return Current.nextSiblingIndex_();
      return getHostSize();
    }

    CNode& getNode(const CIndex& Index) {
      return (Host_->TreeBase_)[Index];
    }
    const CNode& getNode(const CIndex& Index) const {
      return (Host_->TreeBase_)[Index];
    }
    CNode& getCurrentNode() {
      return getNode(Current_);
    }
    const CNode& getCurrentNode() const {
      return getNode(Current_);
    }
    CNode& getParentNode() {
      return getNode(parentIndex_());
    }
    const CNode& getParentNode() const {
      return getNode(parentIndex_());
    }
    CNode& getFirstChildNode() {
      return getNode(firstChildIndex_());
    }
    const CNode& getFirstChildNode() const {
      return getNode(firstChildIndex_());
    }
    CNode& getLastChildNode() {
      return getNode(lastChildIndex_());
    }
    const CNode& getLastChildNode() const {
      return getNode(lastChildIndex_());
    }
    CNode& getPreviousSiblingNode() {
      return getNode(previousSiblingIndex_());
    }
    const CNode& getPreviousSiblingNode() const {
      return getNode(previousSiblingIndex_());
    }
    CNode& getNextSiblingNode() {
      return getNode(nextSiblingIndex_());
    }
    const CNode& getNextSiblingNode() const {
      return getNode(nextSiblingIndex_());
    }

    ~CBaseIterator() = default;

    CHostTreePtr Host_ = nullptr;
    CIndex Current_ = 0;
  };

  template<class TBaseIterator>
  class CNodeReference;

  template<class TBaseIterator>
  class CDataReference : public TBaseIterator {
  public:
    using CBase = TBaseIterator;
    using reference = typename CBase::reference;
    using pointer = typename CBase::pointer;

    CDataReference() = default;

    template<class TOtherBaseIterator>
    friend class CDataReference;
    template<class TOtherBaseIterator>
    CDataReference(const CDataReference<TOtherBaseIterator>& other)
        : CBase(other.Host_, other.Current_) {
    }

    template<class TOtherBaseIterator>
    friend class CNodeReference;

    using CBase::CBase;

    reference operator*() const {
      return CBase::Host_->data(CBase::Current_);
    }
    pointer operator->() const {
      return &CBase::Host_->data(CBase::Current_);
    }
  };

public:
  using CConstBasicIterator =
      CDataReference<CBaseIterator<CConstIteratorDefines>>;

  using CBasicIterator = CDataReference<CBaseIterator<CIteratorDefines>>;

protected:
  template<class TBaseIterator>
  class CNodeReference : public TBaseIterator {
  public:
    using CBase = TBaseIterator;
    using CNodeRef = typename CBase::CNodeRef;
    using CNodePtr = typename CBase::CNode*;

    using CBase::CBase;

    CNodeReference() = default;
    CNodeReference(const CDataReference<TBaseIterator>& other)
        : CBase(other.Host_, other.Current_) {
    }

    CNodeRef operator*() const {
      return (CBase::Host_->TreeBase_)[CBase::Current_];
    }
    CNodePtr operator->() const {
      return &((CBase::Host_->TreeBase_)[CBase::Current_]);
    }
  };

  template<class TIteratorWithDereferencing>
  class CPreOrderLogic : public TIteratorWithDereferencing {
  public:
    using CBase = TIteratorWithDereferencing;
    using CHostTreePtr = typename CBase::CHostTreePtr;
    // using CNodePtr = typename CBase::CNode*;
    using CBase::CBase;

    template<class TIterWithDeref>
    bool operator<(const CPreOrderLogic<TIterWithDeref>& other) const {
      assert(CBase::Host_ == other.Host_);
      if (!CBase::isHostDefined_())
        return false;
      return CBase::Current_ < other.Current_;
    }
    template<class TIterWithDeref>
    bool operator<=(const CPreOrderLogic<TIterWithDeref>& other) const {
      return !(other < *this);
    }
    template<class TIterWithDeref>
    bool operator>(const CPreOrderLogic<TIterWithDeref>& other) const {
      return other < *this;
    }
    template<class TIterWithDeref>
    bool operator>=(const CPreOrderLogic<TIterWithDeref>& other) const {
      return !(*this < other);
    }

  protected:
    void setToNext() {
      assert(CBase::isHostDefined_());
      ++CBase::Current_;
    }
    void setToPrevious() {
      assert(CBase::isHostDefined_());
      --CBase::Current_;
    }
    void moveByOffset(typename CBase::difference_type Offset) {
      assert(CBase::isHostDefined_());
      CBase::Current_ += Offset;
      assert(CBase::isCurrentInFullRange_());
    }
    template<class TIterWithDeref>
    typename CBase::difference_type
    subtract(const CPreOrderLogic<TIterWithDeref>& other) const {
      assert(CBase::Host_ == other.Host_);
      if (!CBase::isHostDefined_())
        return 0;
      return CBase::Current_ - other.Current_;
    }

    ~CPreOrderLogic() = default;
  };

  template<class TIteratorWithDereferencing>
  friend class CPreOrderLogic;

  template<class TIteratorWithDereferencing>
  class CLastSonLogic : public TIteratorWithDereferencing {
  public:
    template<class TOtherIteratorWithDereferencing>
    friend class CLastSonLogic;

    using CBase = TIteratorWithDereferencing;
    using CHostTreePtr = typename CBase::CHostTreePtr;
    // using CNodePtr = typename CBase::CNode*;
    using CBase::CBase;

    template<class TIterWithDeref>
    bool operator<(const CLastSonLogic<TIterWithDeref>& other) const {
      assert(CBase::Host_ == other.Host_);
      if (!CBase::isHostDefined_())
        return false;
      return CBase::Current_ < other.Current_;
    }
    template<class TIterWithDeref>
    bool operator<=(const CLastSonLogic<TIterWithDeref>& other) const {
      return !(other < *this);
    }
    template<class TIterWithDeref>
    bool operator>(const CLastSonLogic<TIterWithDeref>& other) const {
      return other < *this;
    }
    template<class TIterWithDeref>
    bool operator>=(const CLastSonLogic<TIterWithDeref>& other) const {
      return !(*this < other);
    }

  protected:
    void setToNext() {
      assert(CBase::isHostDefined_());
      if (CBase::hasChildren())
        CBase::setToLastChild();
      else
        CBase::Current_ = CBase::getHostSize();
    }
    void setToPrevious() {
      assert(CBase::isHostDefined_());
      if (CBase::isCorrect_()) {
        assert(CBase::hasParent());
        CBase::setToParent();
      } else {
        assert(CBase::Current_ > 0);
        --(CBase::Current_);
      }
    }
    void moveByOffset(typename CBase::difference_type Offset) {
      assert(CBase::isHostDefined_());
      while (Offset > 0) {
        --Offset;
        setToNext();
      }
      while (Offset < 0) {
        ++Offset;
        setToPrevious();
      }
      assert(CBase::isCurrentInFullRange_());
    }
    template<class TIterWithDeref>
    typename CBase::difference_type
    subtract(const CLastSonLogic<TIterWithDeref>& other) const {
      assert(CBase::Host_ == other.Host_);
      if (!CBase::isHostDefined_())
        return 0;
      typename CBase::difference_type difference = 0;
      CLastSonLogic current = *this;
      while (current < other) {
        current.setToNext();
        ++difference;
      }
      while (current > other) {
        current.setToPrevious();
        ++difference;
      }
      return difference;
    }

    ~CLastSonLogic() = default;
  };

  template<class TIteratorWithDereferencing>
  friend class CLastSonLogic;

  template<class TIteratorWithDereferencing>
  class CSiblingLogic : public TIteratorWithDereferencing {
  public:
    template<class TOtherIteratorWithDereferencing>
    friend class CSiblingLogic;

    using CBase = TIteratorWithDereferencing;
    using CHostTreePtr = typename CBase::CHostTreePtr;
    // using CNodePtr = typename CBase::CNode*;
    using CBase::CBase;

    template<class TIterWithDeref>
    bool operator<(const CSiblingLogic<TIterWithDeref>& other) const {
      assert(CBase::Host_ == other.Host_);
      if (!CBase::isHostDefined_())
        return false;
      return CBase::Current_ < other.Current_;
    }
    template<class TIterWithDeref>
    bool operator<=(const CSiblingLogic<TIterWithDeref>& other) const {
      return !(other < *this);
    }
    template<class TIterWithDeref>
    bool operator>(const CSiblingLogic<TIterWithDeref>& other) const {
      return other < *this;
    }
    template<class TIterWithDeref>
    bool operator>=(const CSiblingLogic<TIterWithDeref>& other) const {
      return !(*this < other);
    }

  protected:
    void setToNext() {
      assert(CBase::hasNextSibling());
      CBase::setToNextSibling();
    }
    void setToPrevious() {
      assert(CBase::hasPreviousSibling());
      CBase::setToPreviousSibling();
    }
    void moveByOffset(typename CBase::difference_type Offset) {
      assert(CBase::isHostDefined_());
      while (Offset > 0) {
        --Offset;
        setToNext();
      }
      while (Offset < 0) {
        ++Offset;
        setToPrevious();
      }
      assert(CBase::isCurrentInFullRange_());
    }
    template<class TIterWithDeref>
    typename CBase::difference_type
    subtract(const CSiblingLogic<TIterWithDeref>& other) const {
      assert(CBase::Host_ == other.Host_);
      if (!CBase::isHostDefined_())
        return 0;
      typename CBase::difference_type difference = 0;
      auto current = *this;
      while (current < other) {
        current.setToNext();
        ++difference;
      }
      while (current > other) {
        current.setToPrevious();
        ;
        ++difference;
      }
      return difference;
    }
    ~CSiblingLogic() = default;
  };

  template<class TIteratorWithDereferencing>
  friend class CSiblingLogic;

  template<class TIterratorWithTravellingLogic>
  class CIteratorT : public TIterratorWithTravellingLogic {
    using CBase = TIterratorWithTravellingLogic;

  public:
    using CBase::CBase;
  };

  // Should consider reimplementation in this fasion
  //  template<class T>
  //  class CIteratorT;

  //  using CSiblingIteratorT=CIteratorT<CSiblingLogic<CBasicIterator>>;
  //  using
  //  CConstSiblingIteratorT=CIteratorT<CSiblingLogic<CConstBasicIterator>>;

  template<template<class> class TReferenceLogic,
           template<class> class TTravellingLogic, class TIteratorDefines>
  class CIteratorTemplate;

  using CConstSiblingIterator =
      CIteratorTemplate<CDataReference, CSiblingLogic, CConstIteratorDefines>;

  using CSiblingIterator =
      CIteratorTemplate<CDataReference, CSiblingLogic, CIteratorDefines>;

  template<class TIteratorWithTravellingLogic, class TIteratorDefines>
  class CIteratorChildren;

  template<class TIteratorWithTravellingLogic>
  class CIteratorChildren<TIteratorWithTravellingLogic, CIteratorDefines>
      : public TIteratorWithTravellingLogic {
  public:
    using CChildIterator = CSiblingIterator;
    using CBase = TIteratorWithTravellingLogic;
    using CBase::CBase;
  };

  template<class TIteratorWithTravellingLogic>
  class CIteratorChildren<TIteratorWithTravellingLogic, CConstIteratorDefines>
      : public TIteratorWithTravellingLogic {
  public:
    using CChildIterator = CConstSiblingIterator;
    using CBase = TIteratorWithTravellingLogic;
    using CBase::CBase;
  };

  template<template<class> class TReferenceLogic,
           template<class> class TTravellingLogic, class TIteratorDefines>
  class CIteratorTemplate
      : public CIteratorChildren<
            TTravellingLogic<TReferenceLogic<CBaseIterator<TIteratorDefines>>>,
            TIteratorDefines> {
  public:
    friend CVTree;
    using CBase = CIteratorChildren<
        TTravellingLogic<TReferenceLogic<CBaseIterator<TIteratorDefines>>>,
        TIteratorDefines>;
    using CHostTreePtr = typename CBase::CHostTreePtr;
    using CNodePtr = typename CBase::CNode*;
    using difference_type = typename CBase::difference_type;
    using CChildIterator = typename CBase::CChildIterator;

    template<template<class> class TOtherReferenceLogic,
             template<class> class TOtherTravellingLogic,
             class TOtherIteratorDefines>
    friend class CIteratorTemplate;
    template<template<class> class TOtherReferenceLogic,
             template<class> class TOtherTravellingLogic,
             class TOtherIteratorDefines>
    CIteratorTemplate(
        const CIteratorTemplate<TOtherReferenceLogic, TOtherTravellingLogic,
                                TOtherIteratorDefines>& other)
        : CBase(other.Host_, other.Current_) {
    }
    using CBase::CBase;
    CIteratorTemplate() = default;

  protected:
    CIteratorTemplate(CHostTreePtr HostTree, CIndex Handler)
        : CBase(HostTree, Handler) {
    }

  public:
    CIteratorTemplate& operator++() {
      CBase::setToNext();
      return *this;
    }
    CIteratorTemplate operator++(int) {
      CIteratorTemplate temp = *this;
      ++*this;
      return temp;
    }
    CIteratorTemplate& operator+=(difference_type Difference) {
      CBase::moveByOffset(Difference);
      return *this;
    }
    CIteratorTemplate& operator--() {
      CBase::setToPrevious();
      return *this;
    }
    CIteratorTemplate operator--(int) {
      CIteratorTemplate temp = *this;
      --*this;
      return temp;
    }
    CIteratorTemplate& operator-=(difference_type Difference) {
      CBase::moveByOffset(-Difference);
      return *this;
    }

    template<template<class> class TOtherReferenceLogic,
             class TOtherIteratorDefines>
    difference_type
    operator-(const CIteratorTemplate<TOtherReferenceLogic, TTravellingLogic,
                                      TOtherIteratorDefines>& other) const {
      return CBase::subtract(other);
    }

    CChildIterator FirstChild() const {
      return CChildIterator(CBase::Host_, CBase::lastChildIndex_());
    }
    CChildIterator LastChild() const {
      return CChildIterator(CBase::Host_, CBase::lastChildIndex_());
    }
  };
  template<template<class> class TReferenceLogic,
           template<class> class TTravellingLogic, class TIteratorDefines>
  friend class CIteratorTemplate;

public:
  using CConstPreOrderIterator =
      CIteratorTemplate<CDataReference, CPreOrderLogic, CConstIteratorDefines>;

  using CPreOrderIterator =
      CIteratorTemplate<CDataReference, CPreOrderLogic, CIteratorDefines>;

  using CConstLastSonIterator =
      CIteratorTemplate<CDataReference, CLastSonLogic, CConstIteratorDefines>;

  using CLastSonIterator =
      CIteratorTemplate<CDataReference, CLastSonLogic, CIteratorDefines>;

  using CConstLastSonNodeIterator =
      CIteratorTemplate<CNodeReference, CLastSonLogic, CConstIteratorDefines>;

  CConstPreOrderIterator beginPreOrder() const {
    return CConstPreOrderIterator(this, kRootIndex);
  }
  CConstPreOrderIterator endPreOrder() const {
    return CConstPreOrderIterator(this, size());
  }
  CConstPreOrderIterator cbeginPreOrder() const {
    return beginPreOrder();
  }
  CConstPreOrderIterator cendPreOrder() const {
    return endPreOrder();
  }
  CPreOrderIterator beginPreOrder() {
    return CPreOrderIterator(this, kRootIndex);
  }
  CPreOrderIterator endPreOrder() {
    return CPreOrderIterator(this, size());
  }

  CConstLastSonIterator beginLastSon() const {
    return CConstLastSonIterator(this, kRootIndex);
  }
  CConstLastSonIterator endLastSon() const {
    return CConstLastSonIterator(this, size());
  }
  CConstLastSonIterator cbeginLastSon() const {
    return beginLastSon();
  }
  CConstLastSonIterator cendLastSon() const {
    return endLastSon();
  }
  CLastSonIterator beginLastSon() {
    return CLastSonIterator(this, kRootIndex);
  }
  CLastSonIterator endLastSon() {
    return CLastSonIterator(this, size());
  }

  using const_iterator = CConstPreOrderIterator;
  using iterator = CPreOrderIterator;
  const_iterator begin() const {
    return beginPreOrder();
  }
  const_iterator end() const {
    return endPreOrder();
  }

  const_iterator cbegin() const {
    return begin();
  }
  const_iterator cend() const {
    return end();
  }
  iterator begin() {
    return beginPreOrder();
  }
  iterator end() {
    return endPreOrder();
  }

  template<class TOut>
  friend TOut& operator<<(TOut& out, const CVTree& Tree) {
    for (const auto& element : Tree.TreeBase_) {
      out << element << '\n';
    }
    return out;
  }

  bool hasWeeklyCorrectNumberOfChildren_(CIndex Index) const {
    return (!(numberOfChildren_(Index) == 0) ||
            (!hasFirstChild_(Index) && !hasLastChild_(Index))) &&
           ((numberOfChildren_(Index) == 0) ||
            !(!hasFirstChild_(Index) && !hasLastChild_(Index)));
  }

  bool hasCorrectParent_(CIndex Index) const {
    return !hasParent_(Index) ||
           (hasPreviousSibling_(Index) ||
            firstChildIndex_(parentIndex_(Index)) == Index) ||
           (hasNextSibling_(Index) ||
            lastChildIndex_(parentIndex_(Index)) == Index);
  }
  bool hasCorrectFirstChild_(CIndex Index) const {
    return !hasFirstChild_(Index) ||
           parentIndex_(firstChildIndex_(Index)) == Index;
  }
  bool hasCorrectLastChild_(CIndex Index) const {
    return !hasLastChild_(Index) ||
           parentIndex_(lastChildIndex_(Index)) == Index;
  }
  bool hasCorrectPreviousSibling_(CIndex Index) const {
    return !hasPreviousSibling_(Index) ||
           nextSiblingIndex_(previousSiblingIndex_(Index)) == Index;
  }
  bool hasCorrectNextSibling_(CIndex Index) const {
    return !hasNextSibling_(Index) ||
           previousSiblingIndex_(nextSiblingIndex_(Index)) == Index;
  }

  bool isNodeCorrect_(CIndex Index) const {
    return hasCorrectParent_(Index) && hasCorrectFirstChild_(Index) &&
           hasCorrectLastChild_(Index) && hasCorrectPreviousSibling_(Index) &&
           hasCorrectNextSibling_(Index) &&
           hasWeeklyCorrectNumberOfChildren_(Index);
  }

  bool isStateCorrect_() const {
    for (CIndex i = 0; size_t(i) < TreeBase_.size(); ++i) {
      if (!isNodeCorrect_(i))
        return false;
    }
    return true;
  }
  CIndex getIncorrectNode() const {
    for (CIndex i = 0; size_t(i) < TreeBase_.size(); ++i) {
      if (!isNodeCorrect_(i))
        return i;
    }
    return -1;
  }

private:
  CVTreeBase TreeBase_;
};

} // namespace NSLibrary

#endif // VTREE_H
