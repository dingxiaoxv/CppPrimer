#pragma once

#include <cstddef>
#include <utility>

namespace cpp {

template <typename T>
class UniquePtr {
public:
  UniquePtr() : ptr(nullptr) {}
  explicit UniquePtr(T* p) : ptr(p) {}
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr& operator=(const UniquePtr&) = delete;
  UniquePtr(UniquePtr&& other) noexcept : ptr(other.ptr) { other.ptr = nullptr; }
  UniquePtr& operator=(UniquePtr&& other) noexcept;
  ~UniquePtr();
  T* release();
  void reset(T* p = nullptr);
  T& operator*() const { return *ptr; }
  T* operator->() const { return ptr; }
  T* get() const { return ptr; }
  explicit operator bool() const { return ptr != nullptr; }
  void swap(UniquePtr& other) noexcept;

private:
  T* ptr;
};

template<typename T>
UniquePtr<T>::~UniquePtr() {
  if (ptr) delete ptr;
}

template<typename T>
T* UniquePtr<T>::release() {
  T* temp = ptr;
  ptr = nullptr;
  return temp;
}

template<typename T>
void UniquePtr<T>::reset(T* p) {
  if (ptr) delete ptr;
  ptr = p;
}

template<typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& other) noexcept {
  if (this != &other) {
    if (ptr) delete ptr;
    ptr = other.ptr;
    other.ptr = nullptr;
  }
  return *this;
}

template<typename T>
void UniquePtr<T>::swap(UniquePtr& other) noexcept {
  std::swap(ptr, other.ptr);
}

template<typename T, class... Args>
UniquePtr<T> make_unique_ptr(Args&&... args) {
  return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

}  // namespace cpp