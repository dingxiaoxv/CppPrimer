#ifndef STRVEC_H
#define STRVEC_H

#include <memory>
#include <string>

class StrVec {
public:
  StrVec() : elements_(nullptr), first_free_(nullptr), cap_(nullptr) {}
  StrVec(std::initializer_list<std::string> il);
  StrVec(const StrVec &);
  StrVec &operator=(const StrVec &);
  ~StrVec();
  void push_back(const std::string &);
  void reserve(size_t n) {
    if (n > capacity())
      reallocate(n);
  }
  void resize(size_t n);
  void resize(size_t n, const std::string &);
  size_t size() const { return first_free_ - elements_; }
  size_t capacity() const { return cap_ - elements_; }
  std::string *begin() const { return elements_; }
  std::string *end() const { return first_free_; }

private:
  void chk_n_alloc() {
    if (size() == 0)
      reallocate();
  }
  std::pair<std::string *, std::string *> alloc_n_copy(const std::string *,
                                                       const std::string *);
  void free();
  void reallocate();
  void reallocate(size_t);

private:
  static std::allocator<std::string> alloc_;
  std::string *elements_;
  std::string *first_free_;
  std::string *cap_;
};

#endif