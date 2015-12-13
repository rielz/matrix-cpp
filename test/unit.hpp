#pragma once
#include <iostream>
#include <vector>
#include <chrono>

#ifndef FLOATING_POINT_DELTA
#define FLOATING_POINT_DELTA 0.001
#endif

namespace test
{
	enum class color
	{
		reset = 0,
		
		black = 30 + 0,
		red = 30 + 1,
		green = 30 + 2,
		yellow = 30 + 3,
		blue = 30 + 4,
		magenta = 30 + 5,
		cyan = 30 + 6,
		white = 30 + 7,
	};
	
	std::ostream& operator<<(std::ostream& stream, color c)
	{
		stream << '\x1b' << '[' << static_cast<int>(c) << 'm';
		return stream;
	}
	
	class unit_test;
	class context;

	inline std::vector<unit_test*>& registry()
	{
		static std::vector<unit_test*> tests;
		return tests;
	}
	
	class unit_test
	{
	public:
		unit_test(const char* n) noexcept : n(n)
		{
			registry().push_back(this);
		}
		
		virtual ~unit_test() noexcept 
		{
		}
		
		virtual void run(context& ctx) = 0;
		
		virtual void setup() noexcept { }
		virtual void cleanup() noexcept { }
		
		std::string name()
		{
			return n;
		}
		
	private:
		std::string n;
	};
	
	class context
	{
	public:
		context(unit_test& t) : test(t)
		{
			test.setup();
		}
		
		~context()
		{
			test.cleanup();
		}
		
		void assert(bool condition, const char* message = "assertion failed")
		{
			if (!condition)
			{
				throw std::runtime_error(message);
			}
		}
		
		template<typename T>
		void assert_equals(const T& expected, const T& actual, const char* message = "not equal")
		{
			if (expected != actual)
			{
				throw std::runtime_error(message);
			}
		}
		
		void assert_equals(const float& expected, const float& actual, const char* message = "not equal")
		{
			return assert_between<float>(expected - FLOATING_POINT_DELTA, actual, expected + FLOATING_POINT_DELTA, message);
		}
		
		void assert_equals(const double& expected, const double& actual, const char* message = "not equal")
		{
			return assert_between<double>(expected - FLOATING_POINT_DELTA, actual, expected + FLOATING_POINT_DELTA, message);
		}
		
		template<typename T>
		void assert_not_equals(const T& expected, const T& actual, const char* message = "equal")
		{
			if (expected == actual)
			{
				throw std::runtime_error(message);
			}
		}

		void assert_not_equals(const float& expected, const float& actual, const char* message = "equal")
		{
			return assert_not_between<float>(expected - FLOATING_POINT_DELTA, actual, expected + FLOATING_POINT_DELTA, message);
		}

		void assert_not_equals(const double& expected, const double& actual, const char* message = "equal")
		{
			return assert_not_between<double>(expected - FLOATING_POINT_DELTA, actual, expected + FLOATING_POINT_DELTA, message);
		}
		
		template<typename T>
		void assert_between(const T& lower, const T& actual, const T& upper, const char* message = "not between")
		{
			if (actual < lower || actual > upper)
			{
				throw std::runtime_error(message);
			}
		}
		
		template<typename T>
		void assert_not_between(const T& lower, const T& actual, const T& upper, const char* message = "between")
		{
			if (actual >= lower && actual <= upper)
			{
				throw std::runtime_error(message);
			}
		}
		
		[[noreturn]] void fail(const char* message = "failed")
		{
			throw std::runtime_error(message);
		}
		
	private:
		unit_test& test;
	};
	
	inline bool run(unit_test& t) noexcept
	{
		context ctx(t);
			
		try
		{
			t.run(ctx);
			std::cout << color::green << "[+]" << color::reset << " " << t.name() << " succeeded." << std::endl;
			return true;
		}
		catch (std::exception& e)
		{
			std::cerr << color::red << "[-]" << color::reset << " " << t.name() << " failed: " << e.what() << std::endl;
			return false;
		}
		catch (...)
		{
			std::cerr << color::red << "[-]" << color::reset << " " << t.name() << " failed." << std::endl;
			return false;
		}
	}
	
	inline int run() noexcept
	{
		std::size_t failed = 0;
			
		for (unit_test* test : registry())
		{
			if (!run(*test))
			{
				failed++;
			}
		}
		
		return static_cast<int>(failed);
	}
}

#define TEST(name, count) \
void test_##name##_run(test::context& ctx); \
class test_##name : public test::unit_test \
{ \
public: \
	test_##name() noexcept : test::unit_test(#name) \
	{ \
	} \
	virtual void run(test::context& ctx) override \
	{ \
		for(std::size_t i = 0; i < count; i++) \
			test_##name##_run(ctx); \
	} \
}; \
static test_##name test_##name##_instance{}; \
inline void test_##name##_run(test::context& ctx)

#define ASSERT ctx.assert
#define ASSERT_EQUALS(expected, actual) ctx.assert_equals(expected, actual, #actual " not equals " #expected)