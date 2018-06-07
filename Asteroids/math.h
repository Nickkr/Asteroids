#pragma once

#include <math.h>

struct vec2 {
	float x;
	float y;
};

struct mat4x4
{
	//row_column
	float _00;
	float _10;
	float _20;
	float _30;
	float _01;
	float _11;
	float _21;
	float _31;
	float _02;
	float _12;
	float _22;
	float _32;
	float _03;
	float _13;
	float _23;
	float _33;
};

inline vec2 operator*(vec2 v, float s)
{
	return { s * v.x, s * v.y };
}

inline vec2 operator*(float s, vec2 v)
{
	return v * s ;
}

inline vec2 operator/(vec2 v, float s)
{
	return { s / v.x, s / v.y };
}

inline vec2 operator+(vec2 a, vec2 b)
{
	return { a.x + b.x, a.y + b.y };
}

inline vec2 operator-(vec2 a, vec2 b)
{
	return { a.x - b.x, a.y - b.y };
}

inline vec2& operator+=(vec2& lhs, vec2 rhs)
{
	return lhs = lhs + rhs;
}

inline vec2& operator*=(vec2& lhs, float rhs)
{
	return lhs = lhs * rhs;
}

inline vec2 operator*(mat4x4 M, vec2 v)
{
	//TODO
	return v;
}

inline float dot(vec2 a, vec2 b)
{
	return a.x * b.x + a.y * b.y;
}

inline float length_squared(vec2 a)
{
	return dot(a, a);
}

inline float length(vec2 a)
{
	return sqrtf(length_squared(a));
}

inline vec2 normalized(vec2 a)
{
	return a / length(a);
}

struct rect
{
	vec2 min;
	vec2 max;
};

inline float fmodfPositive(float x, float n)
{
	float r = fmodf(x, n);
	return r < 0 ? r + n : r;
}

inline float squared(float x)
{
	return x * x;
}
