#pragma once
#include "mat.hpp"
#include "vec.hpp"

#include <type_traits>

template<typename Type, std::size_t Size>
struct pack_traits;

template<typename Type>
struct alignas(pack_traits<Type, 2>::pack_type) matrix<Type, 2, 2>
{
	typedef pack_traits<Type, 2> pack_traits;

	union
	{
		typename pack_traits::pack_type columns[2];

		struct
		{
			typename pack_traits::value_type m11, m21;
			typename pack_traits::value_type m12, m22;
		};
	};

	void* operator new(std::size_t count)
	{
		return pack_traits::alloc(count);
	}

	void operator delete(void* ptr)
	{
		pack_traits::free(ptr);
	}
};

template<typename Type>
struct alignas(pack_traits<Type, 4>::pack_type) matrix<Type, 4, 4>
{
	typedef pack_traits<Type, 4> pack_traits;

	union
	{
		typename pack_traits::pack_type columns[4];

		struct
		{
			typename pack_traits::value_type m11, m21, m31, m41;
			typename pack_traits::value_type m12, m22, m32, m42;
			typename pack_traits::value_type m13, m23, m33, m43;
			typename pack_traits::value_type m14, m24, m34, m44;
		};
	};

	void* operator new(std::size_t count)
	{
		return pack_traits::alloc(count);
	}

	void operator delete(void* ptr)
	{
		pack_traits::free(ptr);
	}
};

template<typename Type>
struct alignas(pack_traits<Type, 2>::pack_type) matrix<Type, 2, 1>
{
	typedef pack_traits<Type, 2> pack_traits;

	union
	{
		typename pack_traits::pack_type columns[1];

		struct
		{
			typename pack_traits::value_type x, y;
		};
	};

	void* operator new(std::size_t count)
	{
		return pack_traits::alloc(count);
	}

	void operator delete(void* ptr)
	{
		pack_traits::free(ptr);
	}
};

template<typename Type>
struct alignas(pack_traits<Type, 4>::pack_type) matrix<Type, 4, 1>
{
	typedef pack_traits<Type, 4> pack_traits;

	union
	{
		typename pack_traits::pack_type columns[1];

		struct
		{
			typename pack_traits::value_type x, y, z, w;
		};
	};

	void* operator new(std::size_t count)
	{
		return pack_traits::alloc(count);
	}

	void operator delete(void* ptr)
	{
		pack_traits::free(ptr);
	}
};

template<typename Type>
typename pack_traits<Type, 4>::pack_type dot(const vector<Type, 4>& a, const vector<Type, 4>& b)
{
	typedef pack_traits<Type, 4> op;
	return op::dot(a.columns[0], b.columns[0]);
}

template<typename Type>
inline matrix<Type, 4, 4> operator+(const matrix<Type, 4, 4>& a, const matrix<Type, 4, 4>& b)
{
	typedef pack_traits<Type, 4> op;

	return{
		op::add(a.columns[0], b.columns[0]),
		op::add(a.columns[1], b.columns[1]),
		op::add(a.columns[2], b.columns[2]),
		op::add(a.columns[3], b.columns[3]),
	};
}

template<typename Type>
inline matrix<Type, 4, 1> operator+(const matrix<Type, 4, 1>& a, const matrix<Type, 4, 1>& b)
{
	typedef pack_traits<Type, 4> op;

	return{
		op::add(a.columns[0], b.columns[0]),
	};
}

template<typename Type>
inline matrix<Type, 4, 4> operator*(const matrix<Type, 4, 4>& a, const matrix<Type, 4, 4>& b)
{
	typedef pack_traits<Type, 4> op;

	return{
		op::add(op::mul(op::set(b.m11), a.columns[0]), op::add(op::mul(op::set(b.m21), a.columns[1]), op::add(op::mul(op::set(b.m31), a.columns[2]), op::mul(op::set(b.m41), a.columns[3])))),
		op::add(op::mul(op::set(b.m12), a.columns[0]), op::add(op::mul(op::set(b.m22), a.columns[1]), op::add(op::mul(op::set(b.m32), a.columns[2]), op::mul(op::set(b.m42), a.columns[3])))),
		op::add(op::mul(op::set(b.m13), a.columns[0]), op::add(op::mul(op::set(b.m23), a.columns[1]), op::add(op::mul(op::set(b.m33), a.columns[2]), op::mul(op::set(b.m43), a.columns[3])))),
		op::add(op::mul(op::set(b.m14), a.columns[0]), op::add(op::mul(op::set(b.m24), a.columns[1]), op::add(op::mul(op::set(b.m34), a.columns[2]), op::mul(op::set(b.m44), a.columns[3]))))
	};
}

template<typename Type>
inline matrix<Type, 4, 1> operator*(const matrix<Type, 4, 4>& a, const matrix<Type, 4, 1>& b)
{
	typedef pack_traits<Type, 4> op;

	return{
		op::add(op::mul(op::set(b.x), a.columns[0]), op::add(op::mul(op::set(b.y), a.columns[1]), op::add(op::mul(op::set(b.z), a.columns[2]), op::mul(op::set(b.w), a.columns[3]))))
	};
}

template<typename Type>
inline matrix<Type, 4, 4> operator*(Type c, const matrix<Type, 4, 4>& m)
{
	typedef pack_traits<Type, 4> op;

	op::pack_type factor = op::set(c);
	return{
		op::mul(factor, m.columns[0]),
		op::mul(factor, m.columns[1]),
		op::mul(factor, m.columns[2]),
		op::mul(factor, m.columns[3])
	};
}

template<typename Type>
inline matrix<Type, 4, 1> operator*(Type c, const matrix<Type, 4, 1>& v)
{
	typedef pack_traits<Type, 4> op;

	return{
		op::mul(op::set(c), v.columns[0])
	};
}