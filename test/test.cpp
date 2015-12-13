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

TEST(identity_4x4_float, 1)
{
	auto m = identity<float, 4>();
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

TEST(identity_4x4_int32, 1)
{
	auto m = identity<std::int32_t, 4>();
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

TEST(identity_2x2_float, 1)
{
	auto m = identity<double, 2>();
	ASSERT_EQUALS(1.0, m.m11);
	ASSERT_EQUALS(0.0, m.m21);
	ASSERT_EQUALS(0.0, m.m12);
	ASSERT_EQUALS(1.0, m.m22);
}

TEST(identity_2x2_int64, 1)
{
	auto m = identity<std::int64_t, 2>();
	ASSERT_EQUALS(1l, m.m11);
	ASSERT_EQUALS(0l, m.m21);
	ASSERT_EQUALS(0l, m.m12);
	ASSERT_EQUALS(1l, m.m22);
}

TEST(mul_identity_4x4_float, 1)
{
	matrix<float, 4, 4> m = {
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16	
	};
	
	matrix<float, 4, 4> id = identity<float, 4>();
	ASSERT_EQUALS(m, m * id);
}

int main()
{
	return test::run();
}