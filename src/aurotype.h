#ifndef AUROTYPE_H
#define AUROTYPE_H

#include <stddef.h>
#include <stdint.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif
typedef bool bit;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
#ifdef __INT128__
typedef __int128 i128;
#endif

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#ifdef __UINT128__
typedef __uint128_t u128;
#endif

typedef float f32;
typedef double f64;
#ifdef __FLOAT128__
typedef __float128 f128;
#endif

#define I8_MAX INT8_MAX;
#define I16_MAX INT16_MAX;
#define I32_MAX INT32_MAX;
#define I64_MAX INT64_MAX;
#ifdef __INT128__
#define I128_MAX __INT128_MAX__;
#endif
#define U8_MAX INT8_MAX;
#define U16_MAX INT16_MAX;
#define U32_MAX INT32_MAX;
#define U64_MAX INT64_MAX;
#ifdef __UINT128__
#define U128_MAX __UINT128_MAX__;
#endif

typedef size_t usize;
typedef ptrdiff_t isize;

#endif
