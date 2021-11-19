#ifndef NSLIBRARY_CHEAPWITHACCESS_H
#define NSLIBRARY_CHEAPWITHACCESS_H

#include <algorithm>
#include <vector>

namespace NSLibrary {

template<class Type, class WhatOnTop>
class CHeapWithAccess {
  using CContainer = std::vector<Type>;
  using iterator = typename CContainer::iterator;
  using const_iterator = typename CContainer::const_iterator;

public:
  void make_heap() {
    std::make_heap(Data_.begin(), Data_.end(), WhatOnTop());
  }
  void push(const Type& Element) {
    Data_.push_back(Element);
    std::push_heap(Data_.begin(), Data_.end(), WhatOnTop());
  }
  void push(Type&& Element) {
    Data_.push_back(std::move(Element));
    std::push_heap(Data_.begin(), Data_.end(), WhatOnTop());
  }
  void pop() {
    std::pop_heap(Data_.begin(), Data_.end(), WhatOnTop());
    Data_.pop_back();
  }
  const Type& top() const {
    return Data_.front();
  }
  bool empty() const {
    return Data_.empty();
  }
  size_t size() const {
    return Data_.size();
  }

  iterator begin() {
    return Data_.begin();
  }
  const_iterator begin() const {
    return Data_.begin();
  }
  const_iterator cbegin() const {
    return Data_.cbegin();
  }
  iterator end() {
    return Data_.end();
  }
  const_iterator end() const {
    return Data_.end();
  }
  const_iterator cend() const {
    return Data_.cend();
  }

private:
  CContainer Data_;
};

} // namespace NSLibrary
#endif // NSLIBRARY_CHEAPWITHACCESS_H
