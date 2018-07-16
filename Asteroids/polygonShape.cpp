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

void polygonShape::build(float* vertices, size_t numVertices, float scale)
{
	// Pre-scale mesh
	for (size_t i = 0; i < 2 * numVertices; ++i)
	{
		vertices[i] *= scale;
	}

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

void polygonShape::draw(renderContext& context, mat4x4 const& transform, bool invincible, bool enemyBullet) const
{
	glUniformMatrix4fv(context.modelViewLocation, 1, false, &transform._00);
	
	float lineColor[] = { 1.0f, 1.0f, 1.0f };

	//TODO: only ship to be invisible while dead, other objects get deleted
	if (invincible)
	{
		lineColor[0] = 0.0f;
		lineColor[1] = 1.0f;
		lineColor[2] = 0.0f;
	}
	if (enemyBullet)
	{
		lineColor[0] = 1.0f;
		lineColor[1] = 0.0f;
		lineColor[2] = 0.0f;
	}
	glUniform3fv(context.colorLocation, 1, lineColor);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_LINE_STRIP, 0, numVertices);
}