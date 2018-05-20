// Link statically with GLEW
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Shader sources
const char* vertexSource = R"glsl(
    #version 150 core

    in vec2 position;

    void main()
    {
        gl_Position = vec4(position, 0.0, 1.0);
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

float vertices[] = {
	0.0f,  0.5f, // Vertex 1 (X, Y)
	0.5f, -0.5f, // Vertex 2 (X, Y)
	-0.5f, -0.5f  // Vertex 3 (X, Y)
};

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

int main()
{
	auto window = setupWindow();

	// Initiate GLEW
	glewExperimental = GL_TRUE; // Force GLEW to use a modern OpenGL method for checking if a function is available
	glewInit();

	// Create Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo;
	glGenBuffers(1, &vbo); // Generate 1 buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// Enable vertex attribute array 
	glEnableVertexAttribArray(posAttrib);


	while (!glfwWindowShouldClose(window))
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}