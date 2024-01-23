#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<glm/glm/glm.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<glm/glm/gtc/type_ptr.hpp>

#include "shader_s.h";


const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 800;

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWindow object of 800 by 800 named "OpenGL First Window"
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL First Window", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Enable Depth Testing
	glEnable(GL_DEPTH_TEST);

	// Specify the viewport of OpenGL in the Window
	// In this case the viwport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, WIDTH, HEIGHT);

	Shader shader("shader.vs", "shader.fs");

	// Vertices coordinates
	float vertices[] = {
		// positions         // colors
		 0.5f - 0.25f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f - 0.25f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f - 0.25f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};

	float vertices2[] = {
		// positions         // colors
		0.5f,   0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // front top right
		0.5f,  -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // front bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // front bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f, // front top left 
	};

	float vertices3[] = {
		// positions          // colors
		0.5f,  0.5f, -1.0f,   1.0f, 1.0f, 0.0f, // right top right
		0.5f, -0.5f, -1.0f,   1.0f, 0.0f, 1.0f, // right bottom right
		0.5f,  -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // right bottom left
		0.5f,   0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // right top left
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3,
	};

	float vertices216[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, // left bottom back
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // right bottom back
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // right top back
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // right top back
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, // left top back
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, // left bottom back


		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, // left bottom front
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, // right bottom front
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // right top front
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // right top front
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // left top front
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, // left bottom front


		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // left top front
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, // left top back
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, // left bottom back
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, // left bottom back
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, // left bottom front
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // left top front


		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // right top front
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // right top back
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // right bottom back
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // right bottom back
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, // right bottom front
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // right top front


		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, // left bottom back
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // right bottom back
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, // right bottom front
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, // right bottom front
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, // left bottom front
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, // left bottom back


		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, // left top back
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // right top back
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // right top front
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // right top front
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // left top front
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, // left top back
	};

	float vertices108[] = {
		-0.5f, -0.5f, -0.5f,  // left bottom back
		 0.5f, -0.5f, -0.5f,  // right bottom back
		 0.5f,  0.5f, -0.5f,  // right top back
		 0.5f,  0.5f, -0.5f,  // right top back
		-0.5f,  0.5f, -0.5f,  // left top back
		-0.5f, -0.5f, -0.5f,  // left bottom back


		-0.5f, -0.5f,  0.5f,  // left bottom front
		 0.5f, -0.5f,  0.5f,  // right bottom front
		 0.5f,  0.5f,  0.5f,  // right top front
		 0.5f,  0.5f,  0.5f,  // right top front
		-0.5f,  0.5f,  0.5f,  // left top front
		-0.5f, -0.5f,  0.5f,  // left bottom front


		-0.5f,  0.5f,  0.5f,  // left top front
		-0.5f,  0.5f, -0.5f,  // left top back
		-0.5f, -0.5f, -0.5f,  // left bottom back
		-0.5f, -0.5f, -0.5f,  // left bottom back
		-0.5f, -0.5f,  0.5f,  // left bottom front
		-0.5f,  0.5f,  0.5f,  // left top front


		 0.5f,  0.5f,  0.5f,  // right top front
		 0.5f,  0.5f, -0.5f,  // right top back
		 0.5f, -0.5f, -0.5f,  // right bottom back
		 0.5f, -0.5f, -0.5f,  // right bottom back
		 0.5f, -0.5f,  0.5f,  // right bottom front
		 0.5f,  0.5f,  0.5f,  // right top front


		-0.5f, -0.5f, -0.5f,  // left bottom back
		 0.5f, -0.5f, -0.5f,  // right bottom back
		 0.5f, -0.5f,  0.5f,  // right bottom front
		 0.5f, -0.5f,  0.5f,  // right bottom front
		-0.5f, -0.5f,  0.5f,  // left bottom front
		-0.5f, -0.5f, -0.5f,  // left bottom back


		-0.5f,  0.5f, -0.5f,  // left top back
		 0.5f,  0.5f, -0.5f,  // right top back
		 0.5f,  0.5f,  0.5f,  // right top front
		 0.5f,  0.5f,  0.5f,  // right top front
		-0.5f,  0.5f,  0.5f,  // left top front
		-0.5f,  0.5f, -0.5f,  // left top back
	};

	float vertices10[] = {
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // left bottom back
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // right bottom back
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, // right top back
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, // right top back
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, // left top back
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // left bottom back


		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, // left bottom front
		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, // right bottom front
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // right top front
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // right top front
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // left top front
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, // left bottom front


		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // left top front
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, // left top back
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // left bottom back
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // left bottom back
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, // left bottom front
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // left top front


		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // right top front
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, // right top back
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // right bottom back
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // right bottom back
		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, // right bottom front
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // right top front


		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // left bottom back
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, // right bottom back
		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, // right bottom front
		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f, // right bottom front
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f, // left bottom front
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, // left bottom back


		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, // left top back
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f, // right top back
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // right top front
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // right top front
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, // left top front
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, // left top back
	};

	float vertices14[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,

		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
	};

	// Create reference containers for the Vertex Array Object and the Vertex Buffer Object
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices216), vertices216, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // (void*)0 for vertices108
	glEnableVertexAttribArray(1);
	/*
	unsigned int VAOs[2], VBOs[2], EBOs[2];

	// Always make sure to make a VAO before a VBO
	// Generate the VAO and VBO with 2 objects each
	glGenVertexArrays(2, VAOs); 
	glGenBuffers(2, VBOs);
	glGenBuffers(2, EBOs);

	
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	*/


	// Bind both the VBO and VAO to 0 so that we don't accidentally modify them
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Specify the color of the background
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Clean the back buffer and assign the new color to it
	glClear(GL_COLOR_BUFFER_BIT);
	// Swap the back buffer with the front buffer
	glfwSwapBuffers(window);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// main while loop so the window doesn't close immediately
	while (!glfwWindowShouldClose(window))
	{
		// Process Input (currently just escape -> exit)
		processInput(window);

		// Set BG color
		glClearColor(0.17f, 0.23f, 0.27f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// orthographic projection
		glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, 0.1f, 100.0f);

		// transformations
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::rotate(transform, (float)glfwGetTime()*0.7f, glm::vec3(sinf((float)glfwGetTime()/5.0f), sinf((float)glfwGetTime()/4.0f), tanf((float)glfwGetTime())));

		// Tell OpenGL which Shader Program we want to use
		//glUseProgram(shaderProgram);
		shader.use();
		unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		/*
		glBindVertexArray(VAOs[0]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(VAOs[1]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); 
		*/


		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	/*
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteBuffers(2, EBOs);
	*/
	//glDeleteProgram(shaderProgram);

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}