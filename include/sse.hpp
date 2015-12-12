#pragma once

#ifdef _M_IX86_FP

#if _M_IX86_FP >= 1
#define __SSE__
#endif

#if _M_IX86_FP >= 2
#define __SSE2__
#endif

#endif

#include "mat.hpp"
#include "vec.hpp"
#include "simd.hpp"

#include <cstdint>
#include <atomic>
#include <mutex>

#include <xmmintrin.h>
#include <smmintrin.h>
#include <immintrin.h>

struct sse_traits
{
	static void* alloc(std::size_t count)
	{
		return _mm_malloc(count, 16);
	}

	static void free(void* ptr)
	{
		_mm_free(ptr);
	}
};

template<>
struct pack_traits<double, 2> : public sse_traits
{
	typedef double value_type;
	typedef __m128d pack_type;
	typedef std::integral_constant<std::size_t, 2> pack_size;

	static pack_type add(const pack_type& a, const pack_type& b) { return _mm_add_pd(a, b); }
	static pack_type sub(const pack_type& a, const pack_type& b) { return _mm_sub_pd(a, b); }
	static pack_type mul(const pack_type& a, const pack_type& b) { return _mm_mul_pd(a, b); }
	static pack_type div(const pack_type& a, const pack_type& b) { return _mm_div_pd(a, b); }
	static pack_type set(value_type c) { return _mm_set1_pd(c); }
};

template<>
struct pack_traits<float, 4> : public sse_traits
{
	typedef float value_type;
	typedef __m128 pack_type;
	typedef std::integral_constant<std::size_t, 4> pack_size;

	static pack_type add(const pack_type& a, const pack_type& b) { return _mm_add_ps(a, b); }
	static pack_type sub(const pack_type& a, const pack_type& b) { return _mm_sub_ps(a, b); }
	static pack_type mul(const pack_type& a, const pack_type& b) { return _mm_mul_ps(a, b); }
	static pack_type div(const pack_type& a, const pack_type& b) { return _mm_div_ps(a, b); }
	static pack_type set(value_type c) { return _mm_set1_ps(c); }

	static pack_type dot(const pack_type& a, const pack_type& b)
	{
#ifdef __SSE4_1_
		return _mm_dp_ps(a, b, 0xFF);
#else
		__m128 t1 = _mm_mul_ps(a, b);
		__m128 t2 = _mm_hadd_ps(t1, t1);
		return _mm_hadd_ps(t2, t2);
#endif
	}
};

template<>
struct pack_traits<std::int32_t, 4> : public sse_traits
{
	typedef std::int32_t value_type;
	typedef __m128i pack_type;
	typedef std::integral_constant<std::size_t, 4> pack_size;

	static pack_type add(const pack_type& a, const pack_type& b) { return _mm_add_epi32(a, b); }
	static pack_type sub(const pack_type& a, const pack_type& b) { return _mm_sub_epi32(a, b); }
	static pack_type mul(const pack_type& a, const pack_type& b) { return _mm_mul_epi32(a, b); }
	static pack_type div(const pack_type& a, const pack_type& b);
	static pack_type set(value_type c) { return _mm_set1_epi32(c); }
};

template<>
struct pack_traits<double, 4> : public sse_traits
{
	typedef double value_type;
	typedef __m256d pack_type;
	typedef std::integral_constant<std::size_t, 4> pack_size;

	static pack_type add(const pack_type& a, const pack_type& b) { return _mm256_add_pd(a, b); }
	static pack_type sub(const pack_type& a, const pack_type& b) { return _mm256_sub_pd(a, b); }
	static pack_type mul(const pack_type& a, const pack_type& b) { return _mm256_mul_pd(a, b); }
	static pack_type div(const pack_type& a, const pack_type& b) { return _mm256_div_pd(a, b); }
	static pack_type set(value_type c) { return _mm256_set1_pd(c); }
};

template<>
struct pack_traits<float, 8> : public sse_traits
{
	typedef float value_type;
	typedef __m256 pack_type;
	typedef std::integral_constant<std::size_t, 8> pack_size;

	static pack_type add(const pack_type& a, const pack_type& b) { return _mm256_add_ps(a, b); }
	static pack_type sub(const pack_type& a, const pack_type& b) { return _mm256_sub_ps(a, b); }
	static pack_type mul(const pack_type& a, const pack_type& b) { return _mm256_mul_ps(a, b); }
	static pack_type div(const pack_type& a, const pack_type& b) { return _mm256_div_ps(a, b); }
	static pack_type set(value_type c) { return _mm256_set1_ps(c); }
};

template<>
struct pack_traits<std::int32_t, 8> : public sse_traits
{
	typedef std::int32_t value_type;
	typedef __m256i pack_type;
	typedef std::integral_constant<std::size_t, 8> pack_size;

	static pack_type add(const pack_type& a, const pack_type& b) { return _mm256_add_epi32(a, b); }
	static pack_type sub(const pack_type& a, const pack_type& b) { return _mm256_sub_epi32(a, b); }
	static pack_type mul(const pack_type& a, const pack_type& b) { return _mm256_mul_epi32(a, b); }
	static pack_type div(const pack_type& a, const pack_type& b);
	static pack_type set(value_type c) { return _mm256_set1_epi32(c); }
};

template<>
inline matrix<float, 4, 4> identity<float, 4>()
{
	return{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};
}