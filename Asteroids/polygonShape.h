#pragma once

#include <GL/glew.h>
#include <cstddef>
#include "math.h"
#include "renderContext.h"

class polygonShape
{
public:
	~polygonShape();

	void build(float* vertices, std::size_t numVertices, float scale);

	template <std::size_t N>
	void build(float(&vertices)[N], float scale)
	{
		build(vertices, N / 2, scale);
	}

	void draw(renderContext& context, mat4x4 const& transform, bool invincible) const;

private:
	float* vertices;
	std::size_t numVertices;

	// GPU resources
	GLuint vbo = -1;
	GLuint vao = -1;
};