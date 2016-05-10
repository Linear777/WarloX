#include "Dependencies\glew\glew.h"
#include "Dependencies\glfw\glfw3.h"
#include <iostream>
#include "WindowInit.hpp"
#include "Box.hpp"
#include "GameWork.hpp"
#include "Error.hpp"
#include "ShaderCompilator.hpp"
#include "KeyEvent.hpp"
#include "Dependencies\assimp\anim.h"
#include "Model.hpp"
#include "wogsiw_math.hpp"
#include "Camera.hpp"
#include  "Cubemap.hpp"
#include "FractalDS.hpp"
#include "SkinnedMesh.hpp"
#include "SK.hpp"
#include "wogsiw_pipeline.hpp"
#include "ControlSystem.hpp"
#include "Controls.hpp"
#include "Action.hpp"
#include "MoveAction.hpp"
#include "Character.h"
#include "PerpMove.hpp"
#include "DirectionMove.hpp"
#include "BasicPlayerBehavior.hpp"
#include "SpectatorBehavior.hpp"
#include "rectangle.hpp"

#define CAMERA_CONST_SPEED 50

#define MOUSE_SENSITIVITY 0.5

#define AUDIO_OUTPUT 0.5

//Graphics

#define DRAW_INTER_MODE GL_FILL

KeyEvent* GameWork::inputs;


using namespace WindowSpace;

void GameWork::Init(unsigned short width, unsigned short height,unsigned __int16 fps)
{

	
	WindowInit window(width, height, "Warlox Ignia");
	window.InitWindow(false);

	this->current_context = window.getWindowContext();

	glfwSetKeyCallback(this->current_context, key_callback);
	glfwSetCursorPosCallback(this->current_context,mouse_callback);
	glfwSetInputMode(this->current_context, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (InitOPENGL() == GL_FALSE)
	{
		return;
	}
	glViewport(0,0,width,height);

	PrepareRender();
	RenderCore(fps);

}

GameWork::GameWork()
{}

GameWork::~GameWork()
{}

inline void GameWork::RenderScene(GLfloat dt)
{
	
}

void GameWork::RenderCore(unsigned __int16 fps)
{
	Error::Message(1,"Render Running 60fps");
	Shader loader;
	Shader skymap_shader;

	GLuint program = loader.createProgram("vertex.warloX","fragment.warloX");
	GLuint skybox = skymap_shader.createProgram("cubemap_v.ignia","cubemap_f.ignia");

	vector<Model> vegetation;


	RectangleGround ground(0,0);

	ground.SetUP(1);
	GLuint ground_texture = ground.getTexture("Objects/Environment/Terrain/square_ground.jpg");
	GLuint ground_VAO = ground.VAO;

	vegetation.push_back(Model("Objects/Vegetation/Plants/bush/bush.obj"));
	vegetation.push_back(Model("Objects/Vegetation/Plants/hemp/hemp.obj"));
	vegetation.push_back(Model("Objects/Vegetation/Plants/swirl/swirl.obj"));
	vegetation.push_back(Model("Objects/Vegetation/Trees/tree1/tree1.obj"));
	vegetation.push_back(Model("Objects/Environment/House/House.obj"));
	
	glDepthFunc(GL_LESS);

	vector<const GLchar*> faces;
	faces.push_back("Objects/Environment/skybox/right.jpg");
	faces.push_back("Objects/Environment/skybox/left.jpg");
	faces.push_back("Objects/Environment/skybox/top.jpg");
	faces.push_back("Objects/Environment/skybox/bottom.jpg");
	faces.push_back("Objects/Environment/skybox/back.jpg");
	faces.push_back("Objects/Environment/skybox/front.jpg");

	Cubemap cube = Cubemap();

	GLuint cubeTexture = cube.loadCubemap(faces);
	GLuint cubeVAO = cube.setUp();

	//vegetation.push_back(Model("Objects/Characters/Karen/Karen_Suit.obj"));

	inputs = (KeyEvent*) new KeyEvent();
	camera = new CameraE();


	GLfloat dt = 0;
	GLfloat last_Nanos = 0;
	GLfloat current_Nanos = 0;

	SkinnedMesh * m_mesh = new SkinnedMesh();
	m_mesh->LoadMesh("Objects/Characters/Paladin/Jumpa.dae");
	
	Matrix4f translation;
	translation.InitTranslationTransform(5.f,0,0);

	DirectionalLight m_directionalLight;
	m_directionalLight.Color = Vector3f(1.0f, 1.0f, 1.0f);
	m_directionalLight.AmbientIntensity = 0.55f;
	m_directionalLight.DiffuseIntensity = 0.9f;
	m_directionalLight.Direction = Vector3f(1.0f, 0.0, 0.0);


	SkinningTechnique * tech = new SkinningTechnique();
	tech->Init();
	tech->Enable();
	tech->SetColorTextureUnit(0);
	tech->SetDirectionalLight(m_directionalLight);
	tech->SetMatSpecularIntensity(0.0f);
	tech->SetMatSpecularPower(0);
	PersProjInfo persp;

	persp.FOV = 45;
	persp.Height = 600;
	persp.Width = 800;
	persp.zFar = 1000;
	persp.zNear = 0.1f;


	/*All men are by nature equal, made all of the same earth by one Workman; and however we deceive ourselves, as dear unto God is the poor peasant as the mighty prince.*/

	Object * objecta = new Object();

	Character * player = new Character("Matus Cicman");
	Character * camera_view = new Character("CAMERA");

	objecta->character = player;

	Action * move_front = new MoveAction("move_front");
	Action * move_left = new MoveAction("move_left");

	Action * move_right = new MoveAction("move_right");
	Action * move_back = new MoveAction("move_back");

	ActionAttribs move_front_attribs =	{ "front_move",Vector3f(0, 0, 1), Vector3f(0, 0, 0), 2.f, 0.f, 50.f, 0.f };;
	ActionAttribs move_left_attribs =	{ "left_move", Vector3f(-1, 0, 0), Vector3f(0, 0, 0), 2.f, 0.f, 50.f, 0.f };;
	ActionAttribs move_right_attribs =	{ "right_move", Vector3f(1, 0, 0), Vector3f(0, 0, 0), 2.f, 0.f, 50.f, 0.f };;
	ActionAttribs move_back_attribs =	{ "back_move", Vector3f(0, 0, -1), Vector3f(0, 0, 0), 2.f, 0.f, 50.f, 0.f };;

	move_front->AppendData(move_front_attribs);
	move_left->AppendData(move_left_attribs);
	move_right->AppendData(move_right_attribs);
	move_back->AppendData(move_back_attribs);

	Controls * player_controls = new Controls(1, *objecta);

	player_controls->AddOption(move_front, GLFW_KEY_W);
	player_controls->AddOption(move_left, GLFW_KEY_A);
	player_controls->AddOption(move_right, GLFW_KEY_D);
	player_controls->AddOption(move_back, GLFW_KEY_S);

	player->AddDeltaPosition(Vector3f(300,0,0));

	Controls *camera_controls = new Controls(0, *camera);
	
	Action * move_direction_front = new DirectionMove("move_direction");
	Action * move_perp_left = new PerpMove("perpendicular");
	Action * move_perp_right = new PerpMove("perpendicular");
	Action * move_direction_back = new DirectionMove("perpendicular");

	ActionAttribs move_dir_attribs_f = { "direction", Vector3f(0, 0, 1), Vector3f(0, 0, 0), 2.f, 0.f, 50.f, 0.f };;
	ActionAttribs move_dir_attribs_b = { "direction", Vector3f(0, 0, 1), Vector3f(0, 0, 0), 2.f, 0.f, -50.f, 0.f };;
	ActionAttribs move_perp_attribs_r = { "perpend", Vector3f(0, 0, 1), Vector3f(0, 0, 0), 2.f, 0.f, -50.f, 0.f };;
	ActionAttribs move_perp_attribs_l = { "perpend", Vector3f(0, 0, 1), Vector3f(0, 0, 0), 2.f, 0.f, 50.f, 0.f };;

	move_direction_front->AppendData(move_dir_attribs_f);
	move_direction_back->AppendData(move_dir_attribs_b);
	move_perp_left->AppendData(move_perp_attribs_l);
	move_perp_right->AppendData(move_perp_attribs_r);

	camera_controls->AddOption(move_direction_front, GLFW_KEY_W);
	camera_controls->AddOption(move_perp_left, GLFW_KEY_A);
	camera_controls->AddOption(move_perp_right, GLFW_KEY_D);
	camera_controls->AddOption(move_direction_back, GLFW_KEY_S);

	Object* k = camera;
	k->data.position = Vector3f(0, 0, 0);
	k->data.perpendicular = Vector3f(-1, 0, 0);
	k->data.direction = Vector3f(0,-1,0);
	
	k->character = player;

	ControlSystem system = ControlSystem(2);

	system.addControls(camera_controls);
	system.addControls(player_controls);
	
	BasicPlayerBehavior playerTypeControls = BasicPlayerBehavior();

	playerTypeControls.camera = camera;
	playerTypeControls.character = player;
	playerTypeControls.controls = player_controls;

	BasicSpectatorBehavior spectatorTypeControls = BasicSpectatorBehavior();

	spectatorTypeControls.camera = camera;
	spectatorTypeControls.controls = camera_controls;

	int CURRENT_CONTROLS = 0;
	ControlType *types_control[2];
	types_control[0] = &playerTypeControls;
	types_control[1] = &spectatorTypeControls;

	system.current_controls = types_control[CURRENT_CONTROLS]->controls;
	types_control[CURRENT_CONTROLS]->ChangeBehavior();

	while (!glfwWindowShouldClose(this->current_context))
	{
		//Calculation of delta time from process
		deltaTime = last_Nanos - current_Nanos;

		//Get time from now
		current_Nanos = glfwGetTime();
		
		inputs->mouse_offsets(0,0);

		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		camera->setEulerAngles(inputs->offsets);
		camera->calculateDirection();
		

		for (int i = 0; i < inputs->keyLsize; i++)
		{
			system.current_controls->Execute(inputs->keyL[i]);


			static int ka = 0;
			if (inputs->keyL[i] == 'Q')
			{
				CURRENT_CONTROLS = ++ka % 2;
				system.current_controls = types_control[CURRENT_CONTROLS]->controls;
				types_control[CURRENT_CONTROLS]->ChangeBehavior();

			}
		}
		
		camera->Update();

		tech->Enable();

		float RunningTime = glfwGetTime();

		vector<Matrix4f> Transforms;

		m_mesh->BoneTransform(RunningTime, Transforms);

		for (uint i = 0; i < Transforms.size(); i++) 
		{
			tech->SetBoneTransform(i, Transforms[i]);
		}


		Vector3f cameraPosition = camera->getPosition();
		tech->SetEyeWorldPos(cameraPosition);
		
		Pipeline p;


		p.SetCamera(cameraPosition, camera->getDirection(), camera->getUp());
		p.SetPerspectiveProj(persp);
		p.Scale(0.1f, 0.1f, 0.1f);

		p.WorldPos(player->getPosition());
		tech->SetWVP(p.GetWVPTrans());
		tech->SetWorldMatrix(p.GetWorldTrans());

		m_mesh->Render();
		
		p.WorldPos(Vector3f(0,0,0));
		tech->SetWVP(p.GetWVPTrans());
		tech->SetWorldMatrix(p.GetWorldTrans());

		glUseProgram(program);
		int t = glGetUniformLocation(program, "transform");
		glUniformMatrix4fv(t, 1, GL_TRUE, (const GLfloat*)p.GetWVPTrans());

		for (int i = 0; i < 4;i++)
		vegetation[i].Draw(loader);
		
		p.WorldPos(Vector3f(10,0,10));
		p.Scale(3.f, 3.f, 3.f);
		tech->SetWVP(p.GetWVPTrans());
		tech->SetWorldMatrix(p.GetWorldTrans());
	
		glUniformMatrix4fv(t, 1, GL_TRUE, (const GLfloat*)p.GetWVPTrans());
		vegetation[4].Draw(loader);

		glBindVertexArray(ground_VAO);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(program, "texture_diffuse1"), 0);
		glBindTexture(GL_TEXTURE_2D, ground_texture);
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,(void*)0);
		glBindVertexArray(0);

		Matrix4f camera_trans = p.GetVPTrans();

		camera_trans.m[0][3] = 0;
		camera_trans.m[1][3] = 0;
		camera_trans.m[2][3] = 0;
		camera_trans.m[3][3] = 1;

	
		glDepthFunc(GL_LEQUAL);
		glUseProgram(skybox);

		uint camera_cube = glGetUniformLocation(skybox,"camera");
		uint project_cube = glGetUniformLocation(skybox, "projection");


		glUniformMatrix4fv(project_cube,1,GL_TRUE,(const GLfloat*)camera_trans);
		glUniformMatrix4fv(camera_cube, 1, GL_TRUE, (const GLfloat*)camera_trans);

		glBindVertexArray(cubeVAO);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(skybox, "skybox"),0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		glDepthFunc(GL_LESS);
		
		last_Nanos = glfwGetTime();

		glfwSwapBuffers(this->current_context);
	}

	glfwDestroyWindow(this->current_context);
	glfwTerminate();


	player_controls->Destroy();
	camera_controls->Destroy();
}

void GameWork::PrepareRender()
{
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}


void GameWork::PrepareShaderPath()
{

	

}


bool GameWork::InitOPENGL()
{
	
	if (glewInit() != GLEW_OK)
	{
		Error::Message(0, "Couldn't prepare OpenGL context");
		glfwTerminate();
		return false;
	}
		Error::Message(1, "OpenGL context ready");
	return true;
}


void GameWork::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	static float lastX = 0;
	static float lastY = 0;
	static bool firstMouse = true;

	if (firstMouse) 
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float offsetX = xpos - lastX;
	float offsetY = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	offsetX *= MOUSE_SENSITIVITY;
	offsetY *= MOUSE_SENSITIVITY;

	inputs->mouse_offsets(offsetX,offsetY);
}

void GameWork::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
		return;
	}

	if (action == GLFW_PRESS)
	{
		inputs->press(key);
	}
	else if (action == GLFW_RELEASE)
	{
		inputs->unpress(key);
	}
	
}