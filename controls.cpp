// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix() {
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}

glm::vec3 cameraPos = glm::vec3(4.0f, 0.0f, 4.0f);
glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// Initial Field of View
float initialFoV = 45.0f;
float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float speed = 0.05f; // 2.5 units / second


void computeMatricesFromInputs() {

	// glfwGetTime is called only once, the first time this function is called

	static double lastFrame = glfwGetTime();

	double currentFrame = glfwGetTime();
	// Compute time difference between current and last frame
	float deltaTime = float(currentFrame - lastFrame);
	float speed = 3.0 * deltaTime;

	// cameraDirection : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraDirection = glm::normalize(cameraPos - cameraTarget);

	// cameraRight vector
	glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUp, cameraDirection));

	// cameraUp vector
	cameraUp = glm::cross(cameraDirection, cameraRight);

	// Move forward
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos -= cameraDirection * speed;
	}
	// Move backward
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos += cameraDirection * speed;
	}
	// Strafe cameraRight
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraDirection, cameraUp)) * speed;
	}
	// Strafe left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= glm::normalize(glm::cross(cameraDirection, cameraUp)) * speed;
	}
	// Strafe cameraUp
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraDirection, cameraRight)) * speed;
	}
	// Strafe down
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		cameraPos -= glm::normalize(glm::cross(cameraDirection, cameraRight)) * speed;
	}

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(initialFoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix = glm::lookAt(
		cameraPos,           // Camera is here
		cameraDirection, // and looks here : at the same cameraPosition, plus "cameraDirection"
		cameraUp                  // Head is cameraUp (set to 0,-1,0 to look cameraUpside-down)
	);
	lastFrame = currentFrame;

}