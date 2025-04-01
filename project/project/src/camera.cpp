#include "camera.h"

Camera::Camera(glm::vec3 position = POSITION, glm::vec3 front = FRONT, glm::vec3 world_up = WORLD_UP, float yaw = YAW, float pitch = PITCH, float sens = SENS, float speed = SPEED, float fov = FOV)
{
	this->position = position;
	this->front = front;
	this->world_up = world_up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->sens = sens;
	this->speed = speed;
	this->fov = fov;
	update();
}

glm::mat4 Camera::get_view_matrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::update()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, world_up));
	up = glm::normalize(glm::cross(right, front));
}

void Camera::process_keyboard(directions direction, float delta_time)
{
	float velocity = speed * delta_time;
	if (direction == FORWARD)
		position += speed * front;
	if (direction == BACKWARD)
		position -= speed * front;
	if (direction == LEFT)
		position -= glm::normalize(glm::cross(front, up)) * speed;
	if (direction == RIGHT)
		position += glm::normalize(glm::cross(front, up)) * speed;
}