#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "Observable.h"

class Camera : public Observable {
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
        float yaw = -90.0f,
        float pitch = 0.0f);

    void processKeyboard(GLFWwindow* window, float deltaTime);
    void processMouse(GLFWwindow* window);

    glm::mat4 getViewMatrix() const;
    glm::vec3 getPosition() const { return position; }
    bool changed = false;
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;
    float speed;
    float sensitivity;

    bool firstMouse = true;
    double lastX = 0.0, lastY = 0.0;
    bool rotating = false;
    

};
