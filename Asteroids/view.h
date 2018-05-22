#pragma once
#define GLEW_STATIC
#include "model.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "math.h"
#include <stdio.h>

struct gameObjects
{
	GLuint vao = 0;
	GLuint shipacceleratingvao = 0;
	GLuint asteroidvao = 0;
	GLuint ufovao = 0;
};

gameObjects setupGameObjects();

void drawGameObjects(gameState state, GLuint modelViewLocation);

GLuint setupShaders();