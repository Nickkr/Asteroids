#pragma once

#include "rigidBody.h"
#include "polygonShape.h"
#include "renderContext.h"
#include "math.h"

class fixture
{
public:
	void draw(renderContext& context);

	polygonShape* getShape() const { return shape;  }
	void setShape(polygonShape* shape) { this->shape = shape; }

	rigidBody* getBody() const { return body; }
	void setBody(rigidBody* body) { this->body = body; }

	void setScale(float scale) { this->scale = scale;  }

private:
	mat4x4 computeTransform() const;

	rigidBody* body;
	polygonShape* shape;
	float scale = 1.0f;
};