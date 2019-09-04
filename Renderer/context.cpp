//file
#include "context.h"

//system header
#include <iostream>

//library header
#include "glew/GL/glew.h"
#include "glfw/glfw3.h"

bool context::init(int width, int height, const char * title)
{
	glfwInit();
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewInit();
	std::cout << "OpenGL Version: " << (const char*)glGetString(GL_VERSION) << "\n";
	std::cout << "Renderer: " << (const char*)glGetString(GL_RENDERER) << "\n";
	std::cout << "Vendor: " << (const char*)glGetString(GL_VENDOR) << "\n";
	std::cout << "GLSL: " << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

	glClearColor(.25f, .25f, .25f, 1.0f);

	glEnable(GL_BLEND); // two textures blend together (good for transparency)
	glEnable(GL_DEPTH_TEST); // determine whether parts of object are visible
	glEnable(GL_CULL_FACE); // skip faces that are away from us (optimization)

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // how to blend, in respect to alpha
	glDepthFunc(GL_LEQUAL);  // if z values are <= other z vals, that object gets rendered in front

	return true;
}

void context::tick()
{
	glfwPollEvents();
	glfwSwapBuffers(window);
}

void context::term()
{
	glfwDestroyWindow(window);
	glfwTerminate();
	window = nullptr;
}

void context::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool context::shouldClose() const
{
	return glfwWindowShouldClose(window);
}
