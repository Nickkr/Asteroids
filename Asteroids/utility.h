#pragma once

#include <cstddef>

template <class T, std::size_t N>
std::size_t array_size(T (&)[N])
{
	return N;
}