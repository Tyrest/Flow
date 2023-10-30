#ifndef SHAPE_H
#define SHAPE_H

#include "../shader.h"
#include "../camera.h"

class Shape
{
public:
    Shape(const Shader &shader,
          const glm::vec3 &lightDir,
          const glm::vec3 &color,
          const glm::vec3 &position,
          float angle,
          const glm::vec3 &rotationAxis) : size(1.0f),
                                           shader(shader),
                                           lightDir(lightDir),
                                           color(color),
                                           position(position),
                                           angle(angle),
                                           rotationAxis(rotationAxis) {}
    ~Shape() {}
    void setupShader(const Camera &camera) const;
    virtual void draw(const Camera &camera) const = 0;
    void resize(float factor) { this->size = factor; };
    void move(glm::vec3 position) { this->position = position; };
    void rotate(float angle, glm::vec3 rotationAxis)
    {
        this->angle = angle;
        this->rotationAxis = rotationAxis;
    };
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;

protected:
    float size;
    Shader shader;
    glm::vec3 lightDir;
    glm::vec3 color;
    glm::vec3 position;
    float angle;
    glm::vec3 rotationAxis;

    glm::mat4 transform() const;
};

#endif