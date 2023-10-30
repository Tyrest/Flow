#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <glad/gl.h>
#include "shape.h"

class Cube : public Shape
{
public:
    Cube(const Shader &shader,
         const glm::vec3 &lightDir,
         const glm::vec3 &color = glm::vec3(0.0f, 1.0f, 0.0f),
         const glm::vec3 &position = glm::vec3(0.0f),
         float angle = 0.0f,
         const glm::vec3 &rotation = glm::vec3(0.0f, 1.0f, 0.0f))
        : Shape(shader, lightDir, color, position, angle, rotation) { build(); }

private:
    const static std::vector<float> vertices;
    const static std::vector<uint> indices;

    const std::vector<float> &getVertices() const override { return vertices; };
    const std::vector<uint> &getIndices() const override { return indices; };
    void buildVertices() override{};
};

#endif