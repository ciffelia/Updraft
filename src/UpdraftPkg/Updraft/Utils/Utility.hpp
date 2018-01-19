#pragma once

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
