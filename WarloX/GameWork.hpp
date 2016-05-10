#pragma once

#include "Dependencies\glfw\glfw3.h"

class KeyEvent;
class CameraE;

class GameWork
{

private:
		CameraE* camera;
		GLFWwindow* current_context;	
		static KeyEvent * inputs;

public:
	GameWork();
	~GameWork();

	//Needs to be singleton 
	void Init(unsigned short widt,unsigned short height,unsigned short fps);

	void RenderCore(unsigned __int16);          //Render Logic
	void RenderScene(GLfloat dt);			//Render Current scene
	void PrepareRender(void);       //Prepare Render Engine
	void PrepareShaderPath(void);	//Prepare Shader for load
	bool InitOPENGL();				//Initialize GLEW and GLFW (OpenGL32.lib)

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);	//Keyboard Handler
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);					//Mouse Handler
};