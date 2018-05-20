#include "Controller.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key) {
		case GLFW_KEY_W:
			printf("Keyboard press input: W \n");
			break;
		case GLFW_KEY_A:
			printf("Keyboard press input: A \n");
			break;
		case GLFW_KEY_S:
			printf("Keyboard press input: S \n");
			break;
		case GLFW_KEY_D:
			printf("Keyboard press input: D \n");
			break;
		case GLFW_KEY_SPACE:
			printf("Keyboard press input: SPACE \n");
			break;
		default:
			printf("Keyboard press input: undefined key \n");
			break;
		}
	}

}