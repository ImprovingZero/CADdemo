#include "Visualization.h"

const glm::ivec2 SCREEN_SIZE(1280, 640);
const float FAR_PLANE = 100.0f;
const float NEAR_PLANE = 1.0f;

float xMove = 0.f;
float yMove = 0.f;
float zMove = 0.f;
float xAngle = 0.f;
float yAngle = 0.f;
float zAngle = 0.f;
int Mode = 0;
unsigned int count = 0;
bool keys[1024] = { false };

int Visualization::initGLFW()
{
	if (!glfwInit()) return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	_window = glfwCreateWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "Euler Operation", nullptr, nullptr);
	if (!_window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(_window);
	glewExperimental = GL_TRUE;
	glewInit();
	return 0;
}

/*
void Visualization::initController()
{
	if (!_ctl->Initialize()) {
		std::cout << "Unable to initialize camera!" << std::endl;
	}
	int (*fp)(GLFWwindow * window, int key, int scancode, int action, int mode);
	fp = _ctl->KeyCallback;
	glfwSetKeyCallback(_window, fp);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
*/

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_N && action == GLFW_PRESS) {
		count++;
	}
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void Movement(float deltaTime) 
{
	deltaTime *= 20;
	if (keys[GLFW_KEY_W])
		yMove += 1.0f * deltaTime;
	if (keys[GLFW_KEY_S])
		yMove -= 1.0f * deltaTime;
	if (keys[GLFW_KEY_A])
		xMove -= 1.0f * deltaTime;
	if (keys[GLFW_KEY_D])
		xMove += 1.0f * deltaTime;
	if (keys[GLFW_KEY_Q])
		yAngle += 1.0f * deltaTime*5;
	if (keys[GLFW_KEY_E])
		yAngle -= 1.0f * deltaTime*5;
	if (keys[GLFW_KEY_F])
		Mode ^= 1;
}

Visualization::Visualization()
{
	_ctl = new Controller();
	initGLFW();
	glfwSetKeyCallback(_window, KeyCallback);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//initController();
}

void Visualization::drawAll(geometry::ItemManager* it)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.9f, 0.9f, 0.9f, 1.0);

	GLfloat deltaTime = 0, currentTime = 0;
	GLfloat startTime = glfwGetTime();
	GLfloat lastTime = glfwGetTime();

	while (!glfwWindowShouldClose(_window)) {
		glfwPollEvents();
		GLfloat newTime = glfwGetTime();
		Movement(newTime - lastTime);
		lastTime = newTime;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, SCREEN_SIZE.x, SCREEN_SIZE.y);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluPerspective(45.0f, SCREEN_SIZE.x / SCREEN_SIZE.y, 0.1f, 100.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(xMove, yMove, -10.0f);
		glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
		//glRotatef(zAngle, 0.0f, 0.0f, 1.0f);
		//glRotatef(180.0, 0.0f, 1.0f, 0.0f);
		//it->drawFrame();
		if (Mode == 0) it->drawFace();
		else it->drawFrame();
		//DrawSolid(it->_solid[0]);
		glfwSwapBuffers(_window);
	}
	glfwTerminate();
}
