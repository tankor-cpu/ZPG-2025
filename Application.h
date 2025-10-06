#pragma once
//Include GLEW
#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>
#include "ShaderProgram.h"
#include "Model.h"
#include "Scene.h"

#include <string>
#include <cstdio>
#include <vector>
//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr
#include "Rotation.h"


class Application {
public:
	Application(int width, int height, const char* title);
	~Application();

	void run();
private:
	GLFWwindow* window = nullptr;
	int width;
	int height;
	std::string title;

	ShaderProgram shaderProgram;
	Model model;
	Model model2;
	Model sphereModel;

	static void error_callback(int error, const char* description);
	bool initGLFW_();
	bool initGLEW_();
	bool createWindow_();
	bool createShaders_();
	bool createModels_();
	bool init();
	void mainLoop();
	void cleanup();

	std::vector<Scene*> scenes;
	int currentSceneIndex = 0;

	Rotation* rotation1 = nullptr;
	Rotation* rotation2 = nullptr;

};