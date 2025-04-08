#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 world_up, float yaw, float pitch, float sens, float speed, float fov)
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
	glm::vec3 new_front;
	new_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	new_front.y = sin(glm::radians(pitch));
	new_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(new_front);
	right = glm::normalize(glm::cross(front, world_up));
	up = glm::normalize(glm::cross(right, front));
}

void Camera::process_keyboard(directions direction, float delta_time)
{
	float velocity = speed * delta_time;
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
	if (direction == UP)
		position += up * velocity;
	if (direction == DOWN)
		position -= up * velocity;
}

void Camera::process_mouse(float dx, float dy)
{
	dx *= sens;
	dy *= sens;
	yaw += dx;
	pitch -= dy;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	update();
}

void Camera::process_scroll(float dy)
{
	fov -= (float)dy;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 90.0f)
		fov = 90.f;
}