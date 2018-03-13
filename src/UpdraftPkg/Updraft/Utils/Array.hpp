#pragma once

#include "Types.hpp"

template <class T>
class Array
{
  T *m_data;

  uintn m_size;
  uintn m_capacity;

public:
  Array(const uintn _size = 0);
  
  Array(const Array<T> &array);

  Array<T>& operator=(const Array<T> &array);

  ~Array();

  uintn size() const;

  bool empty() const;

  void reserve(const uintn count);

  T*& data();
  
  const T*& data() const;

  T& at(const uintn pos);

  const T& at(const uintn pos) const;

  T& operator[](const uintn pos);

  const T& operator[](const uintn pos) const;

  T* begin();

  const T* begin() const;

  T* end();

  const T* end() const;

  void push(const T& item);

  template <class... Args>
  void emplace(const Args &... args)
  {
    push(T(args...));
  }

  T& pop();
};

#include "Array_private.hpp"
