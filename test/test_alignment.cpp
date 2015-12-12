#include "test_alignment.hpp"

#include <array>

#define TEST_ITERATIONS 10000

void test_alignment::run(test_context & ctx)
{
	ctx.assert_equal<std::uintptr_t>(alignof(matrix<float, 4, 1>), 16, "matrix<float, 4, 1> must be aligned to 16-byte boundary.");
	ctx.assert_equal<std::uintptr_t>(alignof(matrix<float, 4, 4>), 16, "matrix<float, 4, 4> must be aligned to 16-byte boundary.");
	ctx.assert_equal<std::uintptr_t>(alignof(matrix<double, 2, 1>), 16, "matrix<double, 2, 1> must be aligned to 16-byte boundary.");
	ctx.assert_equal<std::uintptr_t>(alignof(matrix<double, 2, 2>), 16, "matrix<double, 2, 2> must be aligned to 16-byte boundary.");


	for (std::size_t i = 0; i < TEST_ITERATIONS; ++i)
	{
		auto float_4_1_ptr = std::make_unique<matrix<float, 4, 1>>();
		auto float_4_4_ptr = std::make_unique<matrix<float, 4, 4>>();
		auto double_2_1_ptr = std::make_unique<matrix<double, 2, 1>>();
		auto double_2_2_ptr = std::make_unique<matrix<double, 2, 2>>();

		std::uintptr_t float_4_1_value = reinterpret_cast<std::uintptr_t>(float_4_1_ptr.get());
		std::uintptr_t float_4_4_value = reinterpret_cast<std::uintptr_t>(float_4_4_ptr.get());
		std::uintptr_t double_2_1_value = reinterpret_cast<std::uintptr_t>(double_2_1_ptr.get());
		std::uintptr_t double_2_2_value = reinterpret_cast<std::uintptr_t>(double_2_2_ptr.get());

		ctx.assert_equal<std::uintptr_t>(float_4_1_value % 16, 0, "matrix<float, 4, 1> must be aligned to 16-byte boundary.");
		ctx.assert_equal<std::uintptr_t>(float_4_4_value % 16, 0, "matrix<float, 4, 4> must be aligned to 16-byte boundary.");
		ctx.assert_equal<std::uintptr_t>(double_2_1_value % 16, 0, "matrix<double, 2, 1> must be aligned to 16-byte boundary.");
		ctx.assert_equal<std::uintptr_t>(double_2_2_value % 16, 0, "matrix<double, 2, 2> must be aligned to 16-byte boundary.");
	}
}