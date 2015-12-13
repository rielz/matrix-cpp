#pragma once
#include <cstddef>
#include <type_traits>

template <typename Type, std::size_t M, std::size_t N>
struct matrix;

template <typename Type, std::size_t M>
matrix<Type, M, M> identity();

template <typename Type, std::size_t M>
matrix<Type, M, M> pow(const matrix<Type, M, M>& m, unsigned int uiexp);

template <typename Type, std::size_t M, std::size_t N>
bool operator==(const matrix<Type, M, N>& a, const matrix<Type, M, N>& b);

template <typename Type, std::size_t M>
inline matrix<Type, M, M> pow(const matrix<Type, M, M>& m, unsigned int uiexp)
{
    if (uiexp == 0)
    {
		return identity<Type, M>();
    }

    unsigned int mask = ~(~0u >> 1);
    while (!(uiexp & mask))
    {
		mask >>= 1;
    }

    matrix<Type, M, M> r = m;

    while (mask >>= 1)
    {
		r = r * r;
	
		if (uiexp & mask)
		{
			r = r * m;
		}
    }

    return r;
}
