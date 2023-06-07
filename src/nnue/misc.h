/*
  Thanks to Yu Nasu, Hisayori Noda, this implementation adapted from R. De Man
  and Daniel Shaw's Cfish nnue probe code https://github.com/dshawul/nnue-probe
*/

#pragma once

#ifdef _MSC_VER
//#  define _CRT_SECURE_NO_WARNINGS
//#  pragma warning (disable: 4996)
#endif

#include <cinttypes>

#ifdef _WIN32
#  include <Windows.h>
#else
#  include <unistd.h>
#  include <sys/mman.h>
#endif

/*
Force inline
*/
#if defined (__GNUC__)
#   define INLINE  __inline __attribute__((always_inline))
#elif defined (_WIN32)
#   define INLINE  __forceinline
#else
#   define INLINE  __inline
#endif

/*
Intrinsic bsf
*/
#   if defined(__GNUC__)
#       define bsf(b) __builtin_ctzll(b)
#       define bsr(b) (63 - __builtin_clzll(b))
#   elif defined(_WIN32)
#       include <intrin.h>
INLINE int bsf(const uint64_t b) {
	unsigned long x;
	_BitScanForward64(&x, b);
	return static_cast<int>(x);
}
INLINE int bsr(const uint64_t b) {
	unsigned long x;
	_BitScanReverse64(&x, b);
	return static_cast<int>(x);
}
#   endif

#ifdef _WIN32

typedef HANDLE FD;
#define FD_ERR INVALID_HANDLE_VALUE
typedef HANDLE map_t;

#else /* Unix */

typedef int FD;
#define FD_ERR -1
typedef size_t map_t;

#endif

FD open_file(const char* name);
void close_file(FD fd);
size_t file_size(FD fd);
const void* map_file(FD fd, map_t* map);
void unmap_file(const void* data, map_t map);

INLINE uint32_t readu_le_u32(const void* p)
{
	const auto* q = static_cast<const uint8_t*>(p);
	return q[0] | (q[1] << 8) | (q[2] << 16) | (q[3] << 24);
}

INLINE uint16_t readu_le_u16(const void* p)
{
	const auto* q = static_cast<const uint8_t*>(p);
	return q[0] | (q[1] << 8);
}

void decode_fen(const char* fen_str, int* player, int* castle,
	int* fifty, int* move_number, int* piece, int* square);

#define clamp(a, b, c) ((a) < (b) ? (b) : (a) > (c) ? (c) : (a))

