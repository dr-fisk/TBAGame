#ifndef LEST_MATH_HPP
#define LEST_MATH_HPP

namespace lg
{
  namespace Math
  {
    const float PI = 3.14;

    template <typename A, typename B>
    A lerp(const A& crPrev, const A& crNew, const B& crDelta)
    {
      return (crPrev * (1.0f - crDelta)) + (crNew * crDelta);
    }

    static float degreesToRadians(const float cDegrees)
    {
      return cDegrees * (180.0f / PI);
    }
  }
}

#endif