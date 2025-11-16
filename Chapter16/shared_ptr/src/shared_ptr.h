#pragma once

#include <cstddef>
#include <utility>

namespace cpp {

template <typename T>
class SharedPtr {
public:
  SharedPtr() : ptr(nullptr), ref(nullptr) {}
  explicit SharedPtr(T* p) : ptr(p), ref(new std::size_t(1)) {}
  SharedPtr(const SharedPtr& sp) : ptr(sp.ptr), ref(sp.ref) {
    if (ref) {
      ++(*ref);
    }
  }
  SharedPtr(SharedPtr&& sp) noexcept : ptr(sp.ptr), ref(sp.ref) {
    sp.ptr = nullptr;
    sp.ref = nullptr;
  }
  SharedPtr& operator=(const SharedPtr& sp);
  SharedPtr& operator=(SharedPtr&& sp) noexcept;
  ~SharedPtr();
  T& operator*() const { return *ptr; }
  T* operator->() const { return ptr; }
  T* get() const { return ptr; }
  std::size_t use_count() const { return ref ? *ref : 0; }
  explicit operator bool() const { return ptr != nullptr; }
  void reset(T* p = nullptr);
  void swap(SharedPtr& other);

private:
  T* ptr;
  std::size_t* ref;
};

template <typename T>
SharedPtr<T>::~SharedPtr() {
  if (ref && --(*ref) == 0) {
    delete ptr;
    delete ref;
  }
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& rhs) {
  if (rhs.ref) {
    ++(*rhs.ref);
  }

  if (ref && --(*ref) == 0) {
    delete ptr;
    delete ref;
  }

  ptr = rhs.ptr;
  ref = rhs.ref;
  return *this;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& rhs) noexcept {
  if (this != &rhs) {
    if (ref && --(*ref) == 0) {
      delete ptr;
      delete ref;
    }

    ptr = rhs.ptr;
    ref = rhs.ref;
    rhs.ptr = nullptr;
    rhs.ref = nullptr;
  }
  return *this;
}

template <typename T>
void SharedPtr<T>::reset(T* p) {
  if (ref && --(*ref) == 0) {
    delete ptr;
    delete ref;
  }

  if (p) {
    ptr = p;
    ref = new std::size_t(1);
  } else {
    ptr = nullptr;
    ref = nullptr;
  }
}

template <typename T>
void SharedPtr<T>::swap(SharedPtr& other) {
  std::swap(ptr, other.ptr);
  std::swap(ref, other.ref);
}

template <typename T, class... Args>
SharedPtr<T> make_shared_ptr(Args&&... args) {
  return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

}  // namespace cpp