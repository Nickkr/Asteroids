// Link statically with GLEW
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "math.h"
#include "gameState.h"
#include "gameView.h"
#include "fixture.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

// Shader sources
const char* vertexSource = R"glsl(
    #version 150 core

	uniform mat4 modelViewMatrix;

	in vec2 position;

	void main()
	{
		gl_Position = modelViewMatrix * vec4(position, 0.0, 1.0);
	}
)glsl";

const char* fragmentSource = R"glsl(
    #version 150 core

	out vec4 outColor;

	void main()
	{
		outColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
)glsl";

// Check if the shader compiled without an error
void shaderCompileCheck(GLuint shader)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		printf("failed to compile shader");
	}
}

GLFWwindow* setupWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids", nullptr, nullptr); // Windowed
	glfwMakeContextCurrent(window);
	return window;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	gameState* state = reinterpret_cast<gameState*>(glfwGetWindowUserPointer(window));
	switch (key) {
	case GLFW_KEY_UP:
	case GLFW_KEY_W:
		printf("Keyboard press input: W / UP \n");
		state->boostingForward = (action != GLFW_RELEASE);
		break;
	case GLFW_KEY_LEFT:
	case GLFW_KEY_A:
		printf("Keyboard press input: A / LEFT \n");
		state->turnLeft = (action != GLFW_RELEASE);
		break;
	case GLFW_KEY_DOWN:
	case GLFW_KEY_S:
		printf("Keyboard press input: S / DOWN \n");
		state->boostingBackward = (action != GLFW_RELEASE);
		break;
	case GLFW_KEY_RIGHT:
	case GLFW_KEY_D:
		printf("Keyboard press input: D/ RIGHT \n");
		state->turnRight = (action != GLFW_RELEASE);
		break;
	case GLFW_KEY_SPACE:
		printf("Keyboard press input: SPACE \n");
		break;
	default:
		printf("Keyboard press input: undefined key \n");
		break;
	}

}

int main()
{
	gameState state;
	state.setup();

	glfwWindowHint(GLFW_SAMPLES, 4);
	auto window = setupWindow();
	glfwSetWindowUserPointer(window, &state);

	glfwSetKeyCallback(window, key_callback);

	// Initiate GLEW
	glewExperimental = GL_TRUE; // Force GLEW to use a modern OpenGL method for checking if a function is available
	glewInit();

	gameView view(state);
	view.setup();

	// Create and compile the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	shaderCompileCheck(vertexShader);

	// Create and compile the fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	shaderCompileCheck(fragmentShader);

	// Link the vertex and fragment shader into a shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	// Specify the layout of the vertex data
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	renderContext context;
	context.modelViewLocation = glGetUniformLocation(shaderProgram, "modelViewMatrix");
	double timeOfLastUpdate = glfwGetTime();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	while (!glfwWindowShouldClose(window))
	{
		// clear screen to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// process inputs
		glfwPollEvents();

		// check time elapsed since last update call
		double currentUpdateTime = glfwGetTime();
		float dt = static_cast<float>(currentUpdateTime - timeOfLastUpdate);
		timeOfLastUpdate = currentUpdateTime;

		// update game state
		state.update(dt);
		// prepare frame
		view.draw(context);
		// show frame
		glfwSwapBuffers(window);
	}

	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	glfwTerminate();

	return 0;
}