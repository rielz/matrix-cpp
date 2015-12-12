#pragma once
#include <vector>
#include <memory>
#include <ostream>
#include <string>
#include <unordered_set>

#include "color.hpp"

class test_context;

class test
{
public:
	virtual void setup() noexcept
	{
	}

	virtual void cleanup() noexcept
	{
	}

	virtual void run(test_context& ctx) = 0;
};

class test_context
{
public:
	test_context(test& t) noexcept : t(t)
	{
		t.setup();
	}

	~test_context() noexcept
	{
		t.cleanup();
	}

	std::string name()
	{
		return typeid(t).name();
	}

	std::unordered_set<std::string> assertions()
	{
		return errors;
	}

	void assert(bool condition, const char* message = "condition not fulfilled")
	{
		if (!condition)
		{
			errors.emplace(message);
		}
	}

	template<typename T>
	void assert_equal(const T& expected, const T& actual, const char* message = "must not be equal")
	{
		if (expected != actual)
		{
			errors.emplace(message);
		}
	}

	template<typename T>
	void assert_not_equal(const T& expected, const T& actual, const char* message = "must be equal")
	{
		if (expected == actual)
		{
			errors.emplace(message);
		}
	}

	void fail(const char* message = "test failed")
	{
		errors.emplace(message);
	}

private:
	std::unordered_set<std::string> errors;
	test& t;
};

class test_runner
{
public:
	test_runner(std::ostream& output) : output(output)
	{
	}

	void add(test& t)
	{
		tests.push_back(&t);
	}

	void run() noexcept
	{
		unsigned int total = tests.size();
		unsigned int succeeded = 0;

		for (test* t : tests)
		{
			if (run(t))
			{
				succeeded++;
			}
		}

		if (succeeded == total)
		{
			output << color::green;
		}
		else if(succeeded == 0)
		{
			output << color::red;
		}
		else
		{
			output << (color::blue | color::green);
		}

		output << std::endl << succeeded << "/" << total << color::normal << " tests succeeded." << std::endl;
	}

	bool run(test* t) noexcept
	{
		test_context ctx(*t);
		std::string name = ctx.name().substr(6);

		try
		{
			t->run(ctx);
		}
		catch (std::exception& e)
		{
			output << color::red << "[-] " << color::normal << name << " failed: " << color::gray << e.what() << color::normal << std::endl;
			return false;
		}
		catch (...)
		{
			output << color::red << "[-] " << color::normal << name << " failed." << std::endl;
			return false;
		}

		std::unordered_set<std::string> errors = ctx.assertions();

		if (errors.size() == 0)
		{
			return true;
		}
		else
		{
			for (std::string s : errors)
			{
				output << color::red << "[-] " << color::normal << name << " failed: " << color::gray << s << color::normal << std::endl;
			}
			
			return false;
		}
	}

private:
	std::ostream& output;
	std::vector<test*> tests;
};