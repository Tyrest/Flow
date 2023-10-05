#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>
#include "camera.h"

class Input
{
public:
    Input(Camera &camera, GLFWwindow *window)
    {
        this->camera = &camera;
        this->window = window;
    }

    void processInput(float deltaTime)
    {
        this->processControl(deltaTime);
        this->processMovement(deltaTime);
    }

private:
    Camera *camera;
    GLFWwindow *window;

    void processControl(float deltaTime)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

    void processMovement(float deltaTime)
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            this->camera->ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            this->camera->ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            this->camera->ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            this->camera->ProcessKeyboard(RIGHT, deltaTime);
    }
};

#endif