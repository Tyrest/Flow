#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glad/gl.h>
#include "shape.h"

class Sphere : Shape
{
public:
    Sphere();
    ~Sphere();
    void draw()
    {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    static unsigned int VAO;
    static unsigned int VBO;

private:
    const static float vertices[];
};

#endif