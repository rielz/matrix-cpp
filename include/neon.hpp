#pragma once
#include "mat.hpp"
#include "vec.hpp"
#include "simd.hpp"

#include <cstdlib>

#include <arm_neon.h>

struct neon_traits
{
    static void* alloc(std::size_t count) { return ::aligned_alloc(16, count); }
    static void free(void* ptr) { ::free(ptr); }
};

template <>
struct pack_traits<float, 4> : public neon_traits
{
    typedef float value_type;
    typedef float32x4_t pack_type;
    typedef std::integral_constant<std::size_t, 4> pack_size;

    static pack_type add(const pack_type& a, const pack_type& b) { return vaddq_f32(a, b); }
    static pack_type sub(const pack_type& a, const pack_type& b) { return vsubq_f32(a, b); }
    static pack_type mul(const pack_type& a, const pack_type& b) { return vmulq_f32(a, b); }
    static pack_type div(const pack_type& a, const pack_type& b);
    static pack_type set(value_type c) { return vmovq_n_f32(c); }
};
