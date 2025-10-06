#include "Application.h"
#include "CombinedTransformation.h"
#include "Translation.h"
#include "Rotation.h"
#include "Scale.h"

#include "Models/sphere.h"

Application::Application(int width, int height, const char* title)
{
	this->window = nullptr;
	this->width = width;
	this->height = height;
	if (title != nullptr)
		this->title = title;
	else
		this->title = "ZPG";
}
Application::~Application()
{
	cleanup();
}

void Application::run()
{
	if (!init()) {
		fprintf(stderr, "Failed to initialize application\n");
		return;
	}
	
	mainLoop();
	cleanup();
}


void Application::error_callback(int error, const char* description)
{
	std::fputs(description, stderr);
}

bool Application::initGLFW_()
{
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return false;
	}
	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
	return true;
}

bool Application::initGLEW_()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return false;
	}
	return true;
}

bool Application::createWindow_()
{
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window) {
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	return true;
}

bool Application::createShaders_()
{
	if (!shaderProgram.compileFromFile("shaders/default.vert", "shaders/default.frag")) {
		return false;
	}
	return true;
}

bool Application::createModels_()
{
	std::vector<float> pts2 = {
	   -0.6f, -0.4f, 0.0f,   1.0f, 0.0f, 0.0f,
		0.6f, -0.4f, 0.0f,   0.0f, 1.0f, 0.0f,
		0.0f,  0.6f, 0.0f,   0.0f, 0.0f, 1.0f

	};
	model2.setVertices(pts2, 6,0,3);

	std::vector<float> sphereData(sphere, sphere + 17280);
	sphereModel.setVertices(sphereData,
		9,
		0,
		6);
	return true;
}

bool Application::init()
{
	if (!initGLFW_()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return false;
	}
	if (!createWindow_()) {
		fprintf(stderr, "Failed to create window\n");
		return false;
	}
	if (!initGLEW_()) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return false;
	}
	if (!createShaders_()) {
		fprintf(stderr, "Failed to create shaders\n");
		return false;
	}
	if (!createModels_()) {
		fprintf(stderr, "Failed to create models\n");
		return false;
	}

	auto t1 = new CombinedTransformation();
	t1->addTransformation(new Rotation(0.0f, 0.0f, 1.0f, 0.0f));
	t1->addTransformation(new Translation(glm::vec3(-0.5f, 0.0f, 0.0f)));

	auto staticRotation = new Rotation(0.0f, 0.0f, 0.0f, 1.0f);
	auto t2 = new CombinedTransformation();
	t2->addTransformation(staticRotation);
	t2->addTransformation(new Translation(glm::vec3(0.0f, 0.0f, 0.0f)));

	
	
	SceneObject* object2 = new SceneObject(
		new Model(model2),
		new ShaderProgram(shaderProgram),
		t2
	);

	Scene* scene1 = new Scene();
	std::vector<glm::vec3> positions = {
		glm::vec3(0.7f, 0.0f, 0.0f),  // +X
		glm::vec3(-0.7f, 0.0f, 0.0f), // -X
		glm::vec3(0.0f, 0.7f, 0.0f),  // +Y
		glm::vec3(0.0f, -0.7f, 0.0f)  // -Y
	};
	for (auto& pos : positions) {
		auto transform = new CombinedTransformation();
		transform->addTransformation(new Translation(pos));
		transform->addTransformation(new Scale(glm::vec3(0.4f)));

		SceneObject* sphereObject = new SceneObject(
			new Model(sphereModel),
			new ShaderProgram(shaderProgram),
			transform
		);

		scene1->addObject(sphereObject);
	}

	Scene* scene2 = new Scene();
	scene2->addObject(object2);


	scenes.push_back(scene1);
	scenes.push_back(scene2);


	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	return true;
}
void Application::mainLoop()
{

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) currentSceneIndex = 0;
		if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) currentSceneIndex = 1;
		if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) currentSceneIndex = 2;

		float t = static_cast<float>(glfwGetTime());
		

		glm::mat4 V = glm::lookAt(glm::vec3(0, 0, 2),
								  glm::vec3(0, 0, 0),
								  glm::vec3(0, 1, 0));
		//--------------------------------------------------
		float aspect = static_cast<float>(width) / static_cast<float>(height);
		glm::mat4 P = glm::perspective(glm::radians(60.0f), aspect, 0.1f, 100.0f);


		Scene* scene2 = scenes[1];
		auto dynamicRotation = new Rotation(t * 60.0f, 1.0f, 1.0f, 0.0f);
		auto t2 = new CombinedTransformation();
		t2->addTransformation(dynamicRotation);
		t2->addTransformation(new Translation(glm::vec3(0.0f, 0.0f, 0.0f)));
		scene2->getObject(0)->setTransformation(t2);
		
		scenes[currentSceneIndex]->draw(P, V);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
void Application::cleanup()
{
	for (auto scene : scenes) {
		scene->clear();
		delete scene;
	}
	if (window) {
		glfwDestroyWindow(window);
		window = nullptr;
	}
	glfwTerminate();
}


