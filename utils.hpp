#pragma once

#ifdef __APPLE__
#define __ALWAYSINLINE __attribute__((always_inline)) inline
#elif defined(__GNUC__)
#define __ALWAYSINLINE __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
#define __ALWAYSINLINE __forceinline
#else
#define __ALWAYSINLINE inline
#endif
