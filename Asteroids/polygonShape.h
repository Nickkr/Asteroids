#pragma once

#include <GL/glew.h>
#include <cstddef>

class polygonShape
{
public:
	~polygonShape();

	void build(float* vertices, std::size_t numVertices);

	template <std::size_t N>
	void build(float(&vertices)[N])
	{
		build(vertices, N / 2);
	}

	void draw() const;

private:
	float* vertices;
	std::size_t numVertices;

	// GPU resources
	GLuint vbo = -1;
	GLuint vao = -1;
};