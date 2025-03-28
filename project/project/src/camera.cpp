#include "camera.h"

Camera::Camera(glm::vec3 init_position = POSITION, glm::vec3 init_world_up = WORLD_UP, float init_yaw = YAW, float init_pitch = PITCH, float init_sens = SENS, float init_fov = FOV)
{
	position = init_position;
	world_up = init_world_up;
	yaw = init_yaw;
	pitch = init_pitch;
	sens = init_sens;
	fov = init_fov;
	update();
}

glm::mat4 Camera::get_view_matrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::update()
{
	glm::vec3 new_front;
	new_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	new_front.y = sin(glm::radians(pitch));
	new_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(new_front);
	right = glm::normalize(glm::cross(front, world_up));
	up = glm::normalize(glm::cross(right, front));
}