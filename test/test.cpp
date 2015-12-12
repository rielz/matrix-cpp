#include "test_runner.hpp"

#pragma warning (push)
#pragma warning (disable: 4201)
#include "mat.hpp"
#include "vec.hpp"
#include "simd.hpp"
#include "sse.hpp"
#pragma warning (pop)

#include "test_alignment.hpp"

template struct matrix<float, 4, 4>;
template struct matrix<float, 4, 1>;
template struct matrix<double, 2, 2>;
template struct matrix<double, 2, 1>;

#include <iostream>

int main()
{
	test_runner runner(std::cout);
	test_alignment alignment;

	runner.add(alignment);
	runner.run();
}