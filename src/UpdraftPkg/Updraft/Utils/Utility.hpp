#pragma once

void _Swap(void *a, void *b, const size_t size);

template <typename Type>
void Swap(Type &a, Type &b)
{
  _Swap(&a, &b, sizeof(Type));
}

template <typename Type>
constexpr Type Max(const Type &a, const Type &b)
{
  return (a > b) ? a : b;
}

template <typename Type>
constexpr Type Min(const Type &a, const Type &b)
{
  return (a < b) ? a : b;
}

template <typename Type>
constexpr Type Clamp(const Type &x, const Type &min, const Type &max)
{
  return (x < min) ? min : ((max < x) ? max : x);
}
