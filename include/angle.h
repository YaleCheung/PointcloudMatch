#ifndef ANGLE_H
#define ANGLE_H

template<typename T>
   constexpr T Pi = T{3.14159265358979323846264338327950288419717L};

inline auto radToDeg() -> float { return 180.0f / Pi<float>; }
inline auto degToRad() -> float { return Pi<float> / 180.0f; }

#endif // ANGLE_H
