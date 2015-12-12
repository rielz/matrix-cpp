#pragma once
#include "test_runner.hpp"

#pragma warning (push)
#pragma warning (disable: 4201)
#include "mat.hpp"
#include "vec.hpp"
#include "simd.hpp"
#include "sse.hpp"
#pragma warning (pop)

class test_alignment : public test
{
public:
	virtual void run(test_context& ctx);
};