#pragma once

#include "Array.hpp"

extern "C" {
#include <Uefi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
}

template <class T>
Array<T>::Array()
  : m_data(nullptr)
  , m_size(0)
  , m_capacity(0)
{ }

template <class T>
Array<T>::Array(const uintn _size)
  : m_data(new T[_size])
  , m_size(_size)
  , m_capacity(_size)
{ }

template <class T>
Array<T>::Array(const Array<T> &array)
  : m_data(nullptr)
  , m_size(array.m_size)
  , m_capacity(array.m_size)
{
  ::CopyMem(m_data, array.m_data, m_size);
}

template <class T>
Array<T>& Array<T>::operator=(const Array<T>& array)
{
  delete[] m_data;

  m_size = array.m_size;
  m_capacity = array.m_size;

  ::CopyMem(m_data, array.m_data, m_size);

  return *this;
}

template <class T>
Array<T>::~Array()
{
  delete[] m_data;
}

template <class T>
uintn Array<T>::size() const
{
  return m_size;
}

template <class T>
bool Array<T>::empty() const
{
  return m_size == 0;
}

template <class T>
void Array<T>::reserve(const uintn count)
{
  if (count <= m_capacity)
    return;
  
  m_data = ::ReallocatePool(m_size, count, m_data);
  m_capacity = count;
}

template <class T>
T*& Array<T>::data()
{
  return m_data;
}

template <class T>
const T*& Array<T>::data() const
{
  return m_data;
}

template <class T>
T& Array<T>::at(const uintn pos)
{
  Assert(pos < m_size, "Array out of bound.");
  return m_data[pos];
}

template <class T>
const T& Array<T>::at(const uintn pos) const
{
  Assert(pos < m_size, "Array out of bound.");
  return m_data[pos];
}

template <class T>
T& Array<T>::operator[](const uintn pos)
{
  return m_data[pos];
}

template <class T>
const T& Array<T>::operator[](const uintn pos) const
{
  return m_data[pos];
}

template <class T>
void Array<T>::push(const T& item)
{
  if (m_capacity <= m_size)
    reserve(m_capacity * 2);

  m_data[m_size] = item;

  m_size++;
}

template <class T>
T& Array<T>::pop()
{
  return m_data[--m_size];
}
