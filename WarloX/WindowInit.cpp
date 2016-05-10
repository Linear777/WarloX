#include "GameWork.hpp"
#include "WindowInit.hpp"
#include "Dependencies\glfw\glfw3.h"
#include "Error.hpp"

using namespace WindowSpace;

WindowInit::WindowInit()
{
	this->params.WIDTH = 800;
	this->params.HEIGHT = 600;
}
WindowInit::WindowInit(const int width = 800, const int height = 600,char * title = "Default Window")
{
	this->params.WIDTH = width;
	this->params.HEIGHT = height;
	this->params.TITLE = title;
}

WindowInit::~WindowInit()
{

}

void WindowInit::UpdateSettings()
{

	/*Update settings means that we need update GLEW and GLUT for window changable graphics*/

}

WinParams& WindowInit::getParams()
{
	return params;
}
void WindowInit::DestroyWindow()
{

}

void WindowInit::changeSize(const int width, const int height, bool fullscreen)
{
	this->params.WIDTH = width;
	this->params.HEIGHT = height;
	this->params.fullscreen = fullscreen;

}


void WindowInit::InitWindow(bool fullscreen)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);

	this->window_context = glfwCreateWindow(params.WIDTH, params.HEIGHT, params.TITLE, nullptr, nullptr);

	glfwMakeContextCurrent(this->window_context);

	if (this->window_context == NULL)
	{
		Error::Message(0, "Couldn't create window context");
		return;
	}
		Error::Message(1, "Window context created");



}

GLFWwindow* WindowInit::getWindowContext()
{
	return this->window_context;
}

