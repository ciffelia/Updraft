#pragma once

namespace Math {
  constexpr double Pi = 3.1415926535897932385;

  constexpr double TwoPi = Pi * 2.0;

  double Pow(const double x, const double y);

  template <typename Type>
  constexpr Type Square(const Type x)
  {
    return x * x;
  }

  double Sqrt(const double x);

  template <typename Type>
  constexpr Type Abs(const Type x)
  {
    return x >= Type(0) ? x : -x;
  }

  double Sin(const double x);

  double Cos(const double x);

  double Tan(const double x);

  double Asin(const double x);

  double Acos(const double x);

  double Atan(const double x);

  double Atan2(const double y, const double x);
}
