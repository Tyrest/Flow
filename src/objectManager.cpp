#include "objectManager.h"

void ObjectManager::add(Shape *shape)
{
    shapes.push_back(shape);
}

void ObjectManager::draw(Camera &camera, GLFWwindow *window)
{
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    for (uint i = 0; i < shapes.size(); i++)
    {
        shapes[i]->draw(camera);
    }
    // return nothing
}

void ObjectManager::update(float deltaTime)
{
    // for (auto shape : shapes)
    // {
    //     shape.update(deltaTime);
    // }
}

void ObjectManager::processInput(float deltaTime)
{
}

std::vector<Shape *> ObjectManager::shapes;
Camera *ObjectManager::camera;
GLFWwindow *ObjectManager::window;