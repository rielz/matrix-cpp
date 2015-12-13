#include "mat.hpp"
#include "vec.hpp"
#include "simd.hpp"
#include "sse.hpp"

template struct matrix<float, 4, 4>;
template struct matrix<float, 4, 1>;
template struct matrix<std::int32_t, 4, 4>;
template struct matrix<std::int32_t, 4, 1>;
template struct matrix<double, 2, 2>;
template struct matrix<double, 2, 1>;
template struct matrix<std::int64_t, 2, 2>;
template struct matrix<std::int64_t, 2, 1>;

#include "unit.hpp"

#include <memory>
#include <type_traits>

TEST(standard_layout_4x4_float)
{
	typedef matrix<float, 4, 4> mat_4x4_float;
	ASSERT(std::is_standard_layout<mat_4x4_float>::value);
}

TEST(default_constructible_4x4_float)
{
	typedef matrix<float, 4, 4> mat_4x4_float;
	ASSERT(std::is_nothrow_default_constructible<mat_4x4_float>::value);
}

TEST(hash_equal_2x1_double)
{
	std::hash<matrix<double, 2, 1>> hasher;
	matrix<double, 2, 1> v{1, 2};
	
	std::size_t hash_1 = hasher(v);
	std::size_t hash_2 = hasher(v);
	
	ASSERT_EQUALS(hash_1, hash_2);
}

TEST(hash_swapped_2x1_double)
{
	std::hash<matrix<double, 2, 1>> hasher;
	
	matrix<double, 2, 1> v_1{1, 2};
	matrix<double, 2, 1> v_2{2, 1};
	
	std::size_t hash_1 = hasher(v_1);
	std::size_t hash_2 = hasher(v_2);
	
	ASSERT_NOT_EQUALS(hash_1, hash_2);
}

TEST(alignment_4x4_float, 1000)
{
	auto m = std::make_unique<matrix<float, 4, 4>>();
	std::uintptr_t ptr = reinterpret_cast<std::uintptr_t>(m.get());
	ASSERT_EQUALS(0UL, ptr % 16);
}

TEST(alignment_4x1_float, 1000)
{
	auto m = std::make_unique<matrix<float, 4, 1>>();
	std::uintptr_t ptr = reinterpret_cast<std::uintptr_t>(m.get());
	ASSERT_EQUALS(0UL, ptr % 16);
}

TEST(alignment_2x2_double, 1000)
{
	auto m = std::make_unique<matrix<double, 2, 2>>();
	std::uintptr_t ptr = reinterpret_cast<std::uintptr_t>(m.get());
	ASSERT_EQUALS(0UL, ptr % 16);
}

TEST(alignment_2x1_double, 1000)
{
	auto m = std::make_unique<matrix<double, 2, 1>>();
	std::uintptr_t ptr = reinterpret_cast<std::uintptr_t>(m.get());
	ASSERT_EQUALS(0UL, ptr % 16);
}

TEST(identity_4x4_float)
{
	auto m = identity_4x4<float>();
	ASSERT_EQUALS(1.0f, m.m11);
	ASSERT_EQUALS(1.0f, m.m22);
	ASSERT_EQUALS(1.0f, m.m33);
	ASSERT_EQUALS(1.0f, m.m44);
	
	ASSERT_EQUALS(0.0f, m.m12);
	ASSERT_EQUALS(0.0f, m.m13);
	ASSERT_EQUALS(0.0f, m.m14);
	ASSERT_EQUALS(0.0f, m.m21);
	ASSERT_EQUALS(0.0f, m.m23);
	ASSERT_EQUALS(0.0f, m.m24);
	ASSERT_EQUALS(0.0f, m.m31);
	ASSERT_EQUALS(0.0f, m.m32);
	ASSERT_EQUALS(0.0f, m.m34);
	ASSERT_EQUALS(0.0f, m.m41);
	ASSERT_EQUALS(0.0f, m.m42);
	ASSERT_EQUALS(0.0f, m.m43);
}

TEST(identity_4x4_int32)
{
	auto m = identity_4x4<std::int32_t>();
	ASSERT_EQUALS(1, m.m11);
	ASSERT_EQUALS(1, m.m22);
	ASSERT_EQUALS(1, m.m33);
	ASSERT_EQUALS(1, m.m44);
	
	ASSERT_EQUALS(0, m.m12);
	ASSERT_EQUALS(0, m.m13);
	ASSERT_EQUALS(0, m.m14);
	ASSERT_EQUALS(0, m.m21);
	ASSERT_EQUALS(0, m.m23);
	ASSERT_EQUALS(0, m.m24);
	ASSERT_EQUALS(0, m.m31);
	ASSERT_EQUALS(0, m.m32);
	ASSERT_EQUALS(0, m.m34);
	ASSERT_EQUALS(0, m.m41);
	ASSERT_EQUALS(0, m.m42);
	ASSERT_EQUALS(0, m.m43);
}

TEST(identity_2x2_float)
{
	auto m = identity_2x2<double>();
	ASSERT_EQUALS(1.0, m.m11);
	ASSERT_EQUALS(0.0, m.m21);
	ASSERT_EQUALS(0.0, m.m12);
	ASSERT_EQUALS(1.0, m.m22);
}

TEST(identity_2x2_int64)
{
	auto m = identity_2x2<std::int64_t>();
	ASSERT_EQUALS(1l, m.m11);
	ASSERT_EQUALS(0l, m.m21);
	ASSERT_EQUALS(0l, m.m12);
	ASSERT_EQUALS(1l, m.m22);
}

TEST(mul_identity_4x4_float)
{
	matrix<float, 4, 4> m = {
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16	
	};
	
	matrix<float, 4, 4> id = identity_4x4<float>();
	ASSERT_EQUALS(m, m * id);
}

int main()
{
	return test::run();
}