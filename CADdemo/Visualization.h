#pragma once

#include "itemManager.h"
#include <glew.h>
#include <glut.h>
#include <glfw3.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#pragma comment(lib,"OpenGL32.lib")

class Controller
{
	
};

class Visualization
{
private:
	GLFWwindow* _window;
	Controller* _ctl;
	int initGLFW();
	//void initController();
public:
	Visualization();
	void drawAll(geometry::ItemManager* it);

};

