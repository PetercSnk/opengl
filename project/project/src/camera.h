#pragma once
#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum directions {
	FORWARD, BACKWARD, LEFT, RIGHT
};

glm::vec3 POSITION = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 WORLD_UP = glm::vec3(0.0f, 1.0f, 0.0f);
float YAW = -90.0f;
float PITCH = 0.0f;
float SENS = 0.1f;
float FOV = 45.0f;

class Camera
{
public:
	// cameras attributes
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 world_up;
	// euler angles
	float yaw;
	float pitch;
	// camera options
	float sens;
	float fov;
	//
	Camera(glm::vec3 position, glm::vec3 world_up, float yaw, float pitch, float sens, float fov);
	glm::mat4 get_view_matrix();
	void process_keyboard(directions direction, float delta_time);
	void process_mouse(float dx, float dy);
	void process_scroll(float dy);
private:
	void update();
};
#endif // !CAMERA_CLASS_H