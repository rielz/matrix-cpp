#pragma once
#include "mat.hpp"

#include <cmath>
#include <functional>

template <typename Type, std::size_t M>
using vector = matrix<Type, M, 1>;

namespace std
{
	template<typename Type>
	struct hash<matrix<Type, 2, 1>>
	{
		typedef matrix<Type, 2, 1> argument_type;
		typedef std::size_t result_type;
		
		result_type operator()(const argument_type& v) const
		{
			return v.x + (v.y * Type(7));
		}	
	};
}

template <typename Type, std::size_t M>
vector<Type, M> normalize(const vector<Type, M>& v);

template <typename Type, std::size_t M>
Type length(const vector<Type, M>& v);

template <typename Type, std::size_t M>
Type dot(const vector<Type, M>& a, const vector<Type, M>& b);

template <typename Type, std::size_t M>
inline vector<Type, M> normalize(const vector<Type, M>& v)
{
    return v / length(v);
}

template <typename Type, std::size_t M>
inline Type length(const vector<Type, M>& v)
{
    return std::sqrt(dot(v, v));
}
