#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<glm/glm/glm.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<glm/glm/gtc/type_ptr.hpp>

#include "shader_s.h";


const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 800;
const float SPEED = 5.0f;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = (float)WIDTH / 2.0f;
float lastY = (float)HEIGHT / 2.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float rotationDegrees = 0.0f;
float fov = 90.0f;
float nearF = 0.1f;
float farF = 100.0f;


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	} 

	float cameraSpeed = static_cast<float>(SPEED * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	fov -= (float)yoffset * 3;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 130.0f)
		fov = 130.0f;
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
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Load GLAD so it configures OpenGL
	gladLoadGL();

	// Enable Depth Testing
	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	// Create reference containers for the Vertex Array Object and the Vertex Buffer Object
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices10), vertices10, GL_STATIC_DRAW);

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

	glEnable(GL_DEPTH_TEST);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// main while loop so the window doesn't close immediately
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Process Input (currently just escape -> exit)
		processInput(window);

		// Set BG color
		glClearColor(0.17f, 0.23f, 0.27f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* my transformations

		// orthographic projection
		//glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, 0.1f, 100.0f);

		glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

		// transformations
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::rotate(transform, (float)glfwGetTime()*0.7f, glm::vec3(sinf((float)glfwGetTime()/5.0f), sinf((float)glfwGetTime()/4.0f), tanf((float)glfwGetTime())));

		// Tell OpenGL which Shader Program we want to use
		//glUseProgram(shaderProgram);
		shader.use();
		unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

		*/

		shader.use();

		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)WIDTH / (float)HEIGHT, nearF, farF);
		shader.setMat4("projection", projection);

		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		shader.setMat4("view", view);


		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(rotationDegrees + i*50), glm::vec3(sinf(glfwGetTime() + i*8), cosf(glfwGetTime() + i*2), 0.0f));
			shader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		rotationDegrees += 0.05f;
		//glDrawArrays(GL_TRIANGLES, 0, 36);

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