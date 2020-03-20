#pragma once

#ifdef _MSC_VER
    #define ACC_ALWAYSINLINE __forceinline
#elif defined(__clang__) || defined(__GNUC__)
    #define ACC_ALWAYSINLINE inline __attribute__((__always_inline__))
#else
    #define ACC_ALWAYSINLINE inline
#endif

