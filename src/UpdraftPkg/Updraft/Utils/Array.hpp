#pragma once

#include "Types.hpp"

template <class T>
class Array
{
  T *m_data;

  uintn m_size;
  uintn m_capacity;

public:
  Array();

  Array(const Array<T> &array);

  Array<T>& operator=(const Array<T> &array);

  Array(const uintn _size);

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

  void push(const T& item);

  T& pop();
};

#include "Array_private.hpp"
