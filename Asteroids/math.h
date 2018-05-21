#pragma once

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

vec2 operator*(vec2 v, float s)
{
	return { s * v.x, s* v.y };
}

vec2 operator*(float s, vec2 v)
{
	return v * s ;
}

vec2 operator+(vec2 a, vec2 b)
{
	return { a.x + b.x, a.y + b.y };
}

vec2& operator+=(vec2& lhs, vec2 rhs)
{
	return lhs = lhs + rhs;
}

vec2 operator*(mat4x4 M, vec2 v)
{
	//TODO
	return v;
}



