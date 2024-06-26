#include "strvec.h"
#include <iostream>

#define MOVE_ITER

std::allocator<std::string> StrVec::alloc_;

StrVec::StrVec(std::initializer_list<std::string> il) {
  auto newData = alloc_n_copy(il.begin(), il.end());
  elements_ = newData.first;
  first_free_ = cap_ = newData.second;
}

StrVec::StrVec(const StrVec &sv) {
  std::cout << "copy constructor" << std::endl;
  auto newData = alloc_n_copy(sv.elements_, sv.first_free_);
  elements_ = newData.first;
  first_free_ = cap_ = newData.second;
}

StrVec::StrVec(StrVec &&sv) noexcept
    : elements_(sv.elements_), first_free_(sv.first_free_), cap_(sv.cap_) {
  std::cout << "move constructor" << std::endl;
  sv.elements_ = sv.first_free_ = sv.cap_ = nullptr;
}

StrVec &StrVec::operator=(const StrVec &rhs) {
  auto newData = alloc_n_copy(rhs.elements_, rhs.first_free_);
  free();
  elements_ = newData.first;
  first_free_ = cap_ = newData.second;
  return *this;
}

StrVec &StrVec::operator=(StrVec &&rhs) {
  // 处理自赋值
  if (this != &rhs) {
    free();
    elements_ = rhs.elements_;
    first_free_ = rhs.first_free_;
    cap_ = rhs.cap_;
    rhs.elements_ = rhs.first_free_ = rhs.cap_ = nullptr;
  }

  return *this;
}

StrVec::~StrVec() { free(); }

void StrVec::push_back(const std::string &s) {
  chk_n_alloc();
  alloc_.construct(first_free_++, s);
}

void StrVec::push_back(std::string &&s) {
  chk_n_alloc();
  alloc_.construct(first_free_++, std::move(s));
}

void StrVec::resize(size_t n) {
  if (n > size()) {
    while (size() < n) {
      push_back("");
    }
  } else {
    while (size() > n) {
      alloc_.destroy(--first_free_);
    }
  }
}

void StrVec::resize(size_t n, const std::string &s) {
  if (n > size()) {
    while (size() < n) {
      push_back(s);
    }
  }
}

std::pair<std::string *, std::string *>
StrVec::alloc_n_copy(const std::string *b, const std::string *e) {
  auto data = alloc_.allocate(e - b);
  return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free() {
  if (elements_) {
    for (auto p = first_free_; p != elements_;) {
      alloc_.destroy(--p);
    }

    alloc_.deallocate(elements_, cap_ - elements_);
  }
}

void StrVec::reallocate() {
  auto newCapacity = size() ? 2 * size() : 1;
  std::cout << "reallocate capacity " << newCapacity << std::endl;
#ifdef MOVE_ITER
  auto first = alloc_.allocate(newCapacity);
  auto last = std::uninitialized_copy(std::make_move_iterator(begin()),
                                      std::make_move_iterator(end()), first);
  free();
  elements_ = first;
  first_free_ = last;
#else
  auto newData = alloc_.allocate(newCapacity);
  auto dest = newData;
  auto elem = elements_;
  for (size_t i = 0; i < size(); ++i) {
    alloc_.construct(dest++, std::move(*elem++)); // 使用移动构造函数避免拷贝
  }
  free();
  elements_ = newData;
  first_free_ = dest;
#endif
  cap_ = elements_ + newCapacity;
}

void StrVec::reallocate(size_t newCapacity) {
  std::cout << "reallocate capacity " << newCapacity << std::endl;
#ifdef MOVE_ITER
  auto first = alloc_.allocate(newCapacity);
  auto last = std::uninitialized_copy(std::make_move_iterator(begin()),
                                      std::make_move_iterator(end()), first);
  free();
  elements_ = first;
  first_free_ = last;
#else
  auto newData = alloc_.allocate(newCapacity);
  auto dest = newData;
  auto elem = elements_;
  for (size_t i = 0; i < size(); ++i) {
    alloc_.construct(dest++, std::move(*elem++)); // 使用移动构造函数避免拷贝
  }
  free();
  elements_ = newData;
  first_free_ = dest;
#endif
  cap_ = elements_ + newCapacity;
}
