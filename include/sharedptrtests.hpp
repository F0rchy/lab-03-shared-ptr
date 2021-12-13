// Copyright 2021 Artem Artemov <theartemka6@mail.ru>
//

#ifndef INCLUDE_SHAREDPTRTESTS_HPP_
#define INCLUDE_SHAREDPTRTESTS_HPP_

#include <atomic>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>
auto example() -> void;

template <typename T>
class SharedPtr {
 public:
  SharedPtr() {
    ptr = nullptr;
    counter = new std::atomic_uint;
    *counter = 0;
  }

  explicit SharedPtr(T* pointer) {
    counter = new std::atomic_uint;
    ptr = pointer;
    *counter = 1;
  }

  SharedPtr(const SharedPtr& r) {
    ptr = r.ptr;
    counter = r.counter;
    (*counter)++;
  }

  SharedPtr(SharedPtr&& r) {
    ptr = std::move(r.ptr);
    counter = std::move(r.counter);
  }

  ~SharedPtr() {
    if ((*counter) < 2) {
      delete counter;
    } else {
      ptr = nullptr;
      (*counter)--;
    }
  }

  auto operator=(const SharedPtr& r) -> SharedPtr& {
    if ((*counter) > 1) {
      (*counter)--;
    }
    ptr = r.ptr;
    counter = r.counter;
    (*counter)++;
    return *this;
  }

  auto operator=(SharedPtr&& r) -> SharedPtr& {
    if ((*counter) > 1) {
      (*counter)--;
    }
    ptr = std::move(r.ptr);
    counter = std::move(r.counter);
    return *this;
  }

  operator bool() const { return (ptr != nullptr); }

  auto operator*() const -> T& { return (*ptr); }

  auto operator->() const -> T* { return ptr; }

  auto get() -> T* { return ptr; }

  void reset() {
    if (*counter > 1) {
      (*counter)--;
    } else {
      delete counter;
    }
    ptr = nullptr;
    counter = new std::atomic_uint;
    *counter = 0;
  }

  void reset(T* pointer) {
    if (*counter > 1) {
      (*counter)--;
    } else {
      delete counter;
    }
    ptr = pointer;
    counter = new std::atomic_uint;
    *counter = 1;
  }

  void swap(SharedPtr& r) {
    T* temp1 = ptr;
    std::atomic_uint* temp2 = counter;
    ptr = r.ptr;
    counter = r.counter;
    r.ptr = temp1;
    r.counter = temp2;
  }

  auto use_count() const -> size_t {
    if (counter == nullptr) {
      return 0;
    } else {
      return *counter;
    }
  }

 private:
  T* ptr;
  std::atomic_uint* counter;
};

#endif  // INCLUDE_SHAREDPTRTESTS_HPP_
