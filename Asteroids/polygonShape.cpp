#include "polygonShape.h"

polygonShape::~polygonShape()
{
	if (vbo != -1)
	{
		glDeleteBuffers(1, &vbo);
	}
	if (vao != -1)
	{
		glDeleteVertexArrays(1, &vao);
	}
}

void polygonShape::build(float* vertices, size_t numVertices)
{
	// Setup CPU resources
	this->vertices = vertices;
	this->numVertices = numVertices;

	// Setup GPU resources
	// Create a Vertex Buffer Object and copy the vertex data to it
	glGenBuffers(1, &vbo); // Generate 1 buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * numVertices, vertices, GL_STATIC_DRAW);
	// Create a VAO to hold the data layout bindings
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void polygonShape::draw() const
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_LINE_STRIP, 0, numVertices);
}