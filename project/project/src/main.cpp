#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "vbo.h"
#include "vao.h"
#include "ebo.h"
#include "camera.h"

// function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void process_input(GLFWwindow* window);

const unsigned int width = 800;
const unsigned int height = 600;

float m = 0.2f;
float delta_time = 0.0f;
float last_frame = 0.0f;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool first_mouse = true;
float xlast = (float)width / 2.0f;
float ylast = (float)height / 2.0f;

int main()
{
	// initialise and configure glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// window creation
	GLFWwindow* window = glfwCreateWindow(width, height, "temp", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// load opengl function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialise GLAD" << std::endl;
		return -1;
	}

	// build, compile, and link shaders
	const char* v = "C:\\Users\\c1842512\\OneDrive - Cardiff University\\Repo\\opengl\\project\\project\\src\\shaders\\vertex.vert";
	const char* f = "C:\\Users\\c1842512\\OneDrive - Cardiff University\\Repo\\opengl\\project\\project\\src\\shaders\\fragment.frag";
	const char* l = "C:\\Users\\c1842512\\OneDrive - Cardiff University\\Repo\\opengl\\project\\project\\src\\shaders\\light.frag";
	//const char* v = "D:\\Repository\\opengl\\project\\project\\src\\shaders\\vertex.vert";
	//const char* f = "D:\\Repository\\opengl\\project\\project\\src\\shaders\\fragment.frag";
	//const char* l = "D:\\Repository\\opengl\\project\\project\\src\\shaders\\light.frag";
	Shader shader(v, f);
	Shader light(v, l);

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	VBO vbo(sizeof(vertices), vertices);

	VAO vao;
	vao.bind();
	vao.link_attrib(vbo, 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	vao.link_attrib(vbo, 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.unbind();

	VAO light_vao;
	light_vao.bind();
	light_vao.link_attrib(vbo, 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	light_vao.unbind();
	
	//const char* container = "C:\\Users\\c1842512\\OneDrive - Cardiff University\\Repo\\opengl\\project\\project\\src\\textures\\container.jpg";
	//const char* awesomeface = "C:\\Users\\c1842512\\OneDrive - Cardiff University\\Repo\\opengl\\project\\project\\src\\textures\\awesomeface.png";
	//const char* container = "D:\\Repository\\opengl\\project\\project\\src\\textures\\container.jpg";
	//const char* awesomeface = "D:\\Repository\\opengl\\project\\project\\src\\textures\\awesomeface.png";
	//Texture tex1(container, GL_RGB, GL_REPEAT, GL_LINEAR);
	//Texture tex2(awesomeface, GL_RGBA, GL_REPEAT, GL_LINEAR);
	//shader.bind();
	//shader.set_int("texture1", 0);
	//shader.set_int("texture2", 1);

	glEnable(GL_DEPTH_TEST);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;

		glm::vec3 trans;
		trans.x = cos(current_frame) * 6.0f;
		trans.y = sin(current_frame) * 6.0f;
		trans.z = 0.0f;
		//glm::vec3 lightPos = glm::translate(glm::mat4(1.0f), trans) * glm::vec3(0.0f, 0.0f, 0.0f);

		//tex1.bind(GL_TEXTURE0);
		//tex2.bind(GL_TEXTURE1);

		shader.bind();
		shader.set_vec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
		shader.set_vec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		shader.set_vec3("lightPos", trans);
		shader.set_vec3("viewPos", camera.position);

		glm::mat4 projection = glm::perspective(glm::radians(camera.fov), (float)width / (float)height, 0.1f, 100.f);
		glm::mat4 view = camera.get_view_matrix();
		shader.set_mat4("projection", projection);
		shader.set_mat4("view", view);
		glm::mat4 model = glm::mat4(1.0f);
		shader.set_mat4("model", model);
		vao.bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		light.bind();
		light.set_mat4("projection", projection);
		light.set_mat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f));
		model = glm::translate(model, trans);
		light.set_mat4("model", model);
		light_vao.bind();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	vao.del();
	light_vao.del();
	vbo.del();
	shader.del();
	glfwTerminate();
	return 0;
}

// callback function for resizing window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (first_mouse)
	{
		xlast = xpos;
		ylast = ypos;
		first_mouse = false;
	}
	float dx = xpos - xlast;
	float dy = ypos - ylast;
	xlast = xpos;
	ylast = ypos;
	camera.process_mouse(dx, dy);
}

void scroll_callback(GLFWwindow* window, double dx, double dy)
{
	camera.process_scroll(dy);
}

// process input
void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.process_keyboard(FORWARD, delta_time);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.process_keyboard(BACKWARD, delta_time);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.process_keyboard(LEFT, delta_time);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.process_keyboard(RIGHT, delta_time);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.process_keyboard(UP, delta_time);
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		camera.process_keyboard(DOWN, delta_time);
}