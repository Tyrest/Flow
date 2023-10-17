#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <glad/gl.h>
#include "shape.h"

class Sphere : public Shape
{
public:
    Sphere(const Shader &shader, const glm::vec3 &lightDir, const glm::vec3 &color = glm::vec3(0.0f, 1.0f, 0.0f), const glm::vec3 &position = glm::vec3(0.0f), float angle = 0.0f, const glm::vec3 &rotation = glm::vec3(0.0f, 1.0f, 0.0f));
    ~Sphere();
    void draw(const Camera &camera, const glm::mat4 &projection, const glm::mat4 &view) const;
    static unsigned int VAO;
    static unsigned int VBO;

private:
    void clearVectors();
    void addVertex(float x, float y, float z) { vertices.push_back(x), vertices.push_back(y), vertices.push_back(z); }
    void addNormal(float x, float y, float z) { normals.push_back(x), normals.push_back(y), normals.push_back(z); }
    void buildVertices(int sectorCount, int stackCount);
    void buildInterleavedVertices();

    const float *arr;
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> interleavedVertices;
    std::vector<float> toDraw;

    static const float cube_vertices[];
};

#endif