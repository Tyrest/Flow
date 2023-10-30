#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glad/gl.h>
#include "shape.h"

class Sphere : public Shape
{
public:
    Sphere(const Shader &shader,
           const glm::vec3 &lightDir,
           const glm::vec3 &color = glm::vec3(0.0f, 1.0f, 0.0f),
           const glm::vec3 &position = glm::vec3(0.0f),
           float angle = 0.0f,
           const glm::vec3 &rotation = glm::vec3(0.0f, 1.0f, 0.0f))
        : Shape(shader, lightDir, color, position, angle, rotation) { build(); };

private:
    // CONSTANTS
    static const int SECTOR_COUNT = 36;
    static const int STACK_COUNT = 18;

    // VERTICES and INDICES vectors
    void clearVectors();
    void addVertex(float x, float y, float z) { vertices.push_back(x), vertices.push_back(y), vertices.push_back(z); }
    void addNormal(float x, float y, float z) { normals.push_back(x), normals.push_back(y), normals.push_back(z); }
    void buildInterleavedVertices();

    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> interleavedVertices;
    std::vector<uint> indices;

    static const float test_vertices[];
    static const uint test_indices[];

    const std::vector<float> &getVertices() const override { return interleavedVertices; };
    const std::vector<uint> &getIndices() const override { return indices; };
    void buildVertices() override;
};

#endif