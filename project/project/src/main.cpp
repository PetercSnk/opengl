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

// function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

float m = 0.2f;

int main()
{
	// initialise and configure glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// window creation
	GLFWwindow* window = glfwCreateWindow(800, 600, "temp", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// load opengl function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialise GLAD" << std::endl;
		return -1;
	}

	// build, compile, and link shaders
	//const char* v = "C:\\Users\\c1842512\\OneDrive - Cardiff University\\Repo\\opengl\\project\\project\\src\\shaders\\vertex.vert";
	//const char* f = "C:\\Users\\c1842512\\OneDrive - Cardiff University\\Repo\\opengl\\project\\project\\src\\shaders\\fragment.frag";
	const char* v = "D:\\Repository\\opengl\\project\\project\\src\\shaders\\vertex.vert";
	const char* f = "D:\\Repository\\opengl\\project\\project\\src\\shaders\\fragment.frag";
	Shader shader(v, f);

	float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	//glm::mat4 model = glm::mat4(1.0f);
	//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	//glm::mat4 view = glm::mat4(1.0f);
	//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.f);

	VAO vao;
	vao.bind();
	VBO vbo(sizeof(vertices), vertices);
	vao.link_attrib(vbo, 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	vao.link_attrib(vbo, 1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.unbind();
	
	const char* container = "D:\\Repository\\opengl\\project\\project\\src\\textures\\container.jpg";
	const char* awsomeface = "D:\\Repository\\opengl\\project\\project\\src\\textures\\awesomeface.png";
	Texture tex1(container, GL_RGB, GL_REPEAT, GL_LINEAR);
	Texture tex2(awsomeface, GL_RGBA, GL_REPEAT, GL_LINEAR);

	shader.bind();
	shader.set_int("texture1", 0);
	shader.set_int("texture2", 1);


	glEnable(GL_DEPTH_TEST);

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

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		shader.set_mat4fv("projection", projection);

		tex1.bind(GL_TEXTURE0);
		tex2.bind(GL_TEXTURE1);

		shader.set_float("m", m);

		shader.bind();
		vao.bind();

		const float r = 10.0f;
		float cam_x = sin(glfwGetTime()) * r;
		float cam_z = cos(glfwGetTime()) * r;

		glm::mat4 view = glm::lookAt(glm::vec3(cam_x, 0.0f, cam_z),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));

		shader.set_mat4fv("view", view);

		for (unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * (i + 1);
			if (i == 0 || i % 3 == 0) {
				model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.5f, 0.0f));
			}
			else
			{
				model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.5f, 0.0f));
			}
			shader.set_mat4fv("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	vao.del();
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

// process input
void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		if (m >= 1.0f)
			m = 1.0f;
		else
			m += 0.0001f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		if (m <= 0.0f)
			m = 0.0f;
		else
			m -= 0.0001f;
	}
}