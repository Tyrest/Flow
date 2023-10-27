#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "shapes/shape.h"

class ObjectManager
{
public:
    static void add(Shape *shape);
    static void draw(Camera &camera, GLFWwindow *window);
    static void update(float deltaTime);
    static void processInput(float deltaTime);

private:
    static std::vector<Shape *> shapes;
    static Camera *camera;
    static GLFWwindow *window;
};

#endif