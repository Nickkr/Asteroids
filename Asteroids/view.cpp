#include "view.h"

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

//spaceship normal vertices
float vertices[] =
{
	0.5f,  0.00f, // Vertex 1 (X, Y)
	-0.20f, 0.20f, // Vertex 2 (X, Y)
	-0.20f, -0.20f  // Vertex 3 (X, Y)
};

//spaceship acceleration vertices
float shipAcceleratingVertices[] =
{
	0.5f,  0.00f, // Vertex 1 (X, Y)
	-0.20f, 0.20f, // Vertex 2 (X, Y)
	-0.40f, 0.20f,
	-0.20f, 0.20f,
	-0.2f, 0.1f,
	-0.4f, 0.1f,
	-0.2f, 0.1f,
	-0.2f, -0.1f,
	-0.4f, -0.1f,
	-0.2f, -0.1f,
	-0.2f, -0.2f,
	-0.4f, -0.2f,
	-0.2f, -0.2f,
	0.5f,  0.00f// Vertex 3 (X, Y)

};
//asteroid vertices
float vertices2[] =
{
	0.1f,  0.35f,
	0.10f, 0.15f,
	0.3f, 0.15f,
	0.3f, -0.1f,
	0.1f, -0.1f,
	0.1f,  -0.25f,
	-0.15f, -0.25f,
	-0.3f, -0.1f,
	-0.3f, 0.1f,
	-0.2f, 0.3f
};

//UFO vertices
float vertices3[] =
{
	-1.0f,  -1.0f,
	1.0f, -1.0f,
	3.0f, 0.0f,
	-3.0f, 0.0f,
	-1.0f, -1.0f,
	-3.0f, 0.0f,
	-1.0f, 1.0f,
	1.0f,  1.0f,
	3.0f, 0.0f,
	1.0f,  1.0f,
	0.5f, 2.0f,
	-0.5f, 2.0f,
	-1.0f, 1.0f
};


gameObjects setupGameObjects() {

	gameObjects objects;
	// Initiate GLEW
	glewExperimental = GL_TRUE; // Force GLEW to use a modern OpenGL method for checking if a function is available
	glewInit();

	//SHIP standard
	// Create Vertex Array Object
	glGenVertexArrays(1, &objects.vao);
	glBindVertexArray(objects.vao);
	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo;
	glGenBuffers(1, &vbo); // Generate 1 buffer
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//SHIP accelerating
	// Create Vertex Array Object
	glGenVertexArrays(1, &objects.shipacceleratingvao);
	glBindVertexArray(objects.shipacceleratingvao);
	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint shipacceleratingvbo;
	glGenBuffers(1, &shipacceleratingvbo); // Generate 1 buffer
	glBindBuffer(GL_ARRAY_BUFFER, shipacceleratingvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(shipAcceleratingVertices), shipAcceleratingVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//ASTEROID OBJECT
	glGenVertexArrays(1, &objects.asteroidvao);
	glBindVertexArray(objects.asteroidvao);
	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint asteroidvbo;
	glGenBuffers(1, &asteroidvbo); // Generate 1 buffer
	glBindBuffer(GL_ARRAY_BUFFER, asteroidvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//UFO OBJECT
	glGenVertexArrays(1, &objects.ufovao);
	glBindVertexArray(objects.ufovao);
	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint ufovbo;
	glGenBuffers(1, &ufovbo); // Generate 1 buffer
	glBindBuffer(GL_ARRAY_BUFFER, ufovbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	return objects;
}

void drawGameObjects(gameState state, GLuint modelViewLocation)
{
	gameObjects objects = setupGameObjects();
	// clear screen to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (state.accelerating())
	{
		glBindVertexArray(objects.shipacceleratingvao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mat4x4 shipTransform = state.computeShipTransformation();
		glUniformMatrix4fv(modelViewLocation, 1, false, &shipTransform._00);
		glDrawArrays(GL_LINE_STRIP, 0, 14);
	}
	else
	{
		glBindVertexArray(objects.vao);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mat4x4 shipTransform = state.computeShipTransformation();
		glUniformMatrix4fv(modelViewLocation, 1, false, &shipTransform._00);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}

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

GLuint setupShaders()
{
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

	GLint modelViewLocation = glGetUniformLocation(shaderProgram, "modelViewMatrix");
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	return modelViewLocation;
}
