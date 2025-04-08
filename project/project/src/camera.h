#pragma once
#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// options for camera movement
enum directions {
	FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN
};

class Camera
{
public:
	// camera attributes
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 world_up;
	// euler angles -> change to quaternions later
	float yaw;
	float pitch;
	// camera options
	float sens;
	float speed;
	float fov;
	// creates a camera object, uses default args if not specified
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), 
		glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3 world_up = glm::vec3(0.0f, 1.0f, 0.0f), 
		float yaw = -90.0f,
		float pitch = 0.0f,
		float sens = 0.1f,
		float speed = 2.5f,
		float fov = 45.0f);
	// gets glm's lookat matrix
	glm::mat4 get_view_matrix();
	// processes user input and updates the cameras attributes & options
	void process_keyboard(directions direction, float delta_time);
	void process_mouse(float dx, float dy);
	void process_scroll(float dy);
private:
	void update();
};
#endif // !CAMERA_CLASS_H