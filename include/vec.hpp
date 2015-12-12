#pragma once
#include "mat.hpp"

#include <cmath>

template<typename Type, std::size_t M>
using vector = matrix<Type, M, 1>;

template<typename Type, std::size_t M>
vector<Type, M> normalize(const vector<Type, M>& v);

template<typename Type, std::size_t M>
Type length(const vector<Type, M>& v);

template<typename Type, std::size_t M>
Type dot(const vector<Type, M>& a, const vector<Type, M>& b);

template<typename Type, std::size_t M>
inline vector<Type, M> normalize(const vector<Type, M>& v)
{
	return v / length(v);
}

template<typename Type, std::size_t M>
Type length(const vector<Type, M>& v)
{
	return std::sqrt(dot(v, v));
}