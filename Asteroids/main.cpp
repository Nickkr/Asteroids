// Link statically with GLEW

#include "main.h"


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800



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
	glfwWindowHint(GLFW_SAMPLES, 4);
	gameState state;
	auto window = setupWindow();
	glfwSetWindowUserPointer(window, &state);

	glfwSetKeyCallback(window, key_callback);
	
	GLuint modelViewLocation = setupShaders();
	double timeOfLastUpdate = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		//check time elapsed since last update call
		double currentUpdateTime = glfwGetTime();
		float dt = static_cast<float>(currentUpdateTime - timeOfLastUpdate);
		timeOfLastUpdate = currentUpdateTime;

		//update game state
		state.update(dt);
		drawGameObjects(state, modelViewLocation);

		glfwSwapBuffers(window);
	}

	//glDeleteProgram(shaderProgram);
	//glDeleteShader(fragmentShader);
	//glDeleteShader(vertexShader);

	//glDeleteBuffers(1, &vbo);

	//glDeleteVertexArrays(1, &vao);

	glfwTerminate();

	return 0;
}