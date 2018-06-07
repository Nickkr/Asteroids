#pragma once

#include "rigidBody.h"
#include "circleShape.h"
#include "renderContext.h"
#include "math.h"

class fixture
{
public:
	circleShape* getShape() const { return shape;  }
	void setShape(circleShape* shape) { this->shape = shape; }

	rigidBody* getBody() const { return body; }
	void setBody(rigidBody* body) { this->body = body; }

	mat4x4 computeTransform() const;

private:
	rigidBody* body;
	circleShape* shape;
};