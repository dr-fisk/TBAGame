#ifndef COMMON_H
#define COMMON_H

#include <cmath>

enum Status {
    FAIL,
    SUCCESS
};

template <typename T>
static bool decimalCmp(T a, T b)
{
  return (fabs(a - b) <= std::numeric_limits<float>::epsilon() * std::max(fabs(a), fabs(b)));
}

#endif