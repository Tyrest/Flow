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
          const glm::vec3 &rotationAxis) : built(false),
                                           size(1.0f),
                                           shader(shader),
                                           lightDir(lightDir),
                                           color(color),
                                           position(position),
                                           angle(angle),
                                           rotationAxis(rotationAxis) {}
    ~Shape();
    void setupShader(const Camera &camera) const;
    void draw(const Camera &camera) const;
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
    bool built;
    float size;
    Shader shader;
    glm::vec3 lightDir;
    glm::vec3 color;
    glm::vec3 position;
    float angle;
    glm::vec3 rotationAxis;

    virtual const std::vector<float> &getVertices() const = 0;
    virtual const std::vector<uint> &getIndices() const = 0;
    virtual void buildVertices() = 0;
    void build();
    glm::mat4 transform() const;
};

#endif